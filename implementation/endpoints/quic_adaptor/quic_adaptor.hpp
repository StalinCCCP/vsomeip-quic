#include <boost/asio/ip/udp.hpp>
namespace quic_adaptor{
class quic_client_adaptor{
    public:
    using endpoint=boost::asio::ip::udp::endpoint;
    using socket=boost::asio::ip::udp::socket;
};
}