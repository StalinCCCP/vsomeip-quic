#include <iomanip>
#include <iostream>
#include <sstream>
#include <condition_variable>
#include <thread>
#include <chrono>
#include <vsomeip/vsomeip.hpp>

#define SAMPLE_SERVICE_ID 0x1234
#define SAMPLE_INSTANCE_ID 0x5678
#define SAMPLE_METHOD_ID 0x0421

std::shared_ptr< vsomeip::application > app;
std::mutex mutex;
std::condition_variable condition;
std::time_t time_before_request;

void run() {
	std::unique_lock<std::mutex> its_lock(mutex);
	condition.wait(its_lock);

	std::shared_ptr< vsomeip::message > request;
	request = vsomeip::runtime::get()->create_request();
	request->set_service(SAMPLE_SERVICE_ID);
	request->set_instance(SAMPLE_INSTANCE_ID);
	request->set_method(SAMPLE_METHOD_ID);

	std::shared_ptr< vsomeip::payload > its_payload = vsomeip::runtime::get()->create_payload();
	std::vector< vsomeip::byte_t > its_payload_data;
	for (vsomeip::byte_t i = 0; i < 10; i++) {
		its_payload_data.push_back(i % 256);
	}
	its_payload->set_data(its_payload_data);
	request->set_payload(its_payload);
	auto now = std::chrono::system_clock::now();
	time_before_request = std::chrono::system_clock::to_time_t(now);

	app->send(request);
}

void on_message(const std::shared_ptr<vsomeip::message>& _response) {
	auto now = std::chrono::system_clock::now();
	std::time_t now_time = std::chrono::system_clock::to_time_t(now);
	std::chrono::seconds delay_time = std::chrono::seconds(now_time) + std::chrono::seconds(time_before_request);

	std::shared_ptr<vsomeip::payload> its_payload = _response->get_payload();
	vsomeip::length_t l = its_payload->get_length();

	std::stringstream ss;
	for (vsomeip::length_t i = 0; i < l; i++) {
		ss << std::setw(2) << std::setfill('0') << std::hex
			<< (int)*(its_payload->get_data() + i) << " ";
	}

	std::cout << "CLIENT: Received message with Client/Session ["
		<< std::setw(4) << std::setfill('0') << std::hex << _response->get_client() << "/"
		<< std::setw(4) << std::setfill('0') << std::hex << _response->get_session() 
		<< ",delay_time:" << std::setw(4) << std::setfill('0') << std::hex
		<< delay_time.count() * 1000 << "ms] " << ss.str() << std::endl;
}

void on_availability(vsomeip::service_t _service, vsomeip::instance_t _instance, bool _is_available) {
	std::cout << "CLIENT: Service ["
		<< std::setw(4) << std::setfill('0') << std::hex << _service << "." << _instance
		<< "] is "
		<< (_is_available ? "available." : "NOT available.")
		<< std::endl;
	condition.notify_one();
}

int main() {

	app = vsomeip::runtime::get()->create_application("Hello");
	app->init();
	app->register_availability_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, on_availability);
	app->request_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);
	app->register_message_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_METHOD_ID, on_message);
	std::thread sender(run);
	app->start();
}