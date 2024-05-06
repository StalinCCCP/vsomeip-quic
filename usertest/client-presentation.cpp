#include <array>
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <memory>
#include <mutex>
#include <string>
#include <vsomeip/runtime.hpp>
#include <vsomeip/vsomeip.hpp>
#include "json/include/nlohmann/json.hpp"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <thread>
#define SAMPLE_SERVICE_ID 0x1234
#define SAMPLE_INSTANCE_ID 0x5678
#define SAMPLE_METHOD_ID 0x0421
std::shared_ptr< vsomeip::application > app;
std::condition_variable condition;
std::chrono::time_point<std::chrono::system_clock> time_before_request;
boost::asio::io_context io;
boost::asio::ip::tcp::acceptor acceptor(io,boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),1234));
//std::shared_ptr<boost::asio::ip::tcp::socket> Socket;
std::mutex mutex;
//boost::asio::ip::tcp::socket Socket;
const size_t Send=10000;
void on_availability(vsomeip::service_t _service, vsomeip::instance_t _instance, bool _is_available) {
        std::cout << "CLIENT: Service ["
                << std::setw(4) << std::setfill('0') << std::hex << _service << "." << _instance
                << "] is "
                << (_is_available ? "available." : "NOT available.")
                << std::endl;
	if(_is_available){
        	condition.notify_one();
	}
}
std::string create_http_response(nlohmann::json &&json){
    auto content=json.dump();
    std::string s="HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: "
        +std::to_string(content.size())
        +"\r\nConnection: close\r\n"
        +content;
    std::cout<<s<<'\n';
    return s;
}
int msgcnt;
std::vector<std::shared_ptr<boost::asio::ip::tcp::socket>> sockets;
int sendcnt;
void on_message(const std::shared_ptr<vsomeip::message>& _response) {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    auto delay_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-time_before_request);

    std::shared_ptr<vsomeip::payload> its_payload = _response->get_payload();
    vsomeip::length_t l = its_payload->get_length();

    std::stringstream ss;
    for (vsomeip::length_t i = 0; i < l; i++) {
            ss << std::setw(2) << std::setfill('0') << std::hex
                    << (int)*(its_payload->get_data() + i) << " ";
    }
    ++msgcnt;
    if(msgcnt==Send){
        msgcnt=0;
        //time_before_request=now;
        std::cout<<"Sending\n";
        boost::asio::write(*sockets[sendcnt],boost::asio::buffer(
            create_http_response(nlohmann::json{
                    {"sent",Send},
                    {"success",Send},//fake success data
                    {"latency",delay_time.count()}
                })
            )
        );
        sockets[sendcnt]->shutdown(boost::asio::ip::tcp::socket::shutdown_send);  // 关闭写入
        sockets[sendcnt]->close();  // 关闭套接字
        ++sendcnt;
    }
    // std::cout << "CLIENT: Received message with Client/Session ["
    //         << std::setw(4) << std::setfill('0') << std::hex << _response->get_client() << "/"
    //         << std::setw(4) << std::setfill('0') << std::hex << _response->get_session() << std::dec 
    //         << ",delay_time:" << delay_time.count()  << "ms] " << ss.str() << std::endl;
}
void run(){
    std::unique_lock<std::mutex> lock(mutex);
    condition.wait(lock);
    std::shared_ptr< vsomeip::message > request;

    request = vsomeip::runtime::get()->create_request();
    request->set_service(SAMPLE_SERVICE_ID);
    request->set_instance(SAMPLE_INSTANCE_ID);
    request->set_method(SAMPLE_METHOD_ID);
    request->set_reliable(true);
    std::cout<<"Running before creating payload\n";
    std::shared_ptr< vsomeip::payload > its_payload = vsomeip::runtime::get()->create_payload();
    std::cout<<"Waiting for connection\n";

    std::vector< vsomeip::byte_t > its_payload_data;
    for (vsomeip::byte_t i = 0; i < 100; i++) {
            its_payload_data.push_back(i % 256);
    }

    its_payload->set_data(its_payload_data);
    request->set_payload(its_payload);
    std::array<char, 1024> buffer;
    for(;;){
        std::array<char, 1024> buffer;
        //Socket=std::make_shared<boost::asio::ip::tcp::socket>(io);
        sockets.emplace_back(std::make_shared<boost::asio::ip::tcp::socket>(io));
        acceptor.accept(*sockets.back());
        auto bytes=sockets.back()->read_some(boost::asio::buffer(buffer));
        std::string req(buffer.data(),bytes);
        if(req.substr(0,3) == "GET"){
            std::cout<<"Connection incoming\n";
            time_before_request=std::chrono::system_clock::now();
            for(int i=0;i<Send;i++)
                app->send(request);
        }
    }
}
int main(){
    std::ios::sync_with_stdio(0),std::cin.tie(0),std::cout.tie(0);
    app = vsomeip::runtime::get()->create_application("Hello");
    app->init();
    app->register_availability_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, on_availability);
    app->request_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);
    app->register_message_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_METHOD_ID, on_message);
    std::thread sender(run);
    app->start();
}