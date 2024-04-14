#include <nexus/quic/stream.hpp>
#include <nexus/quic/client.hpp>
namespace quic_adaptor{
class quic_client_adaptor{
    public:
    using endpoint=boost::asio::ip::udp::endpoint;
    using socket=boost::asio::ip::udp::socket;
};
}