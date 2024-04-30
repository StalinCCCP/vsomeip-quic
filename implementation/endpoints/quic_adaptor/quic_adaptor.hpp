#pragma once
#include <boost/asio/ip/udp.hpp>
namespace quic_adaptor{
class quic_client_adaptor{
    public:
    using endpoint=boost::asio::ip::udp::endpoint;
    using socket=boost::asio::ip::udp::socket;
};
class quic_server_adaptor{
    public:
    using endpoint=boost::asio::ip::udp::endpoint;
    using socket=boost::asio::ip::udp::socket;
};
// class quic_global_init{
//     public:
//     static nexus::global::context global;//nexus::global::init_client_server(); 
// };
}