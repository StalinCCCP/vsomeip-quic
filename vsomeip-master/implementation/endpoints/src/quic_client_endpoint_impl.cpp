#include <iomanip>
#include <sstream>
#include <thread>

#include <boost/asio/ip/multicast.hpp>
#include <vsomeip/internal/logger.hpp>

#include "../include/endpoint_host.hpp"
#include "../include/tp.hpp"
#include "../../routing/include/routing_host.hpp"
#include "../include/quic_client_endpoint_impl.hpp"
#include "../../utility/include/utility.hpp"
#include "../../utility/include/byteorder.hpp"

#define quic_unimplemented
#ifndef quic_unimplemented
namespace vsomeip_v3 {
nexus::global::context vsomeip_v3::quic_client_endpoint_impl::global= nexus::global::init_client();
quic_client_endpoint_impl::quic_client_endpoint_impl(
        const std::shared_ptr<endpoint_host>& _endpoint_host,
        const std::shared_ptr<routing_host>& _routing_host,
        const endpoint_type& _local,
        const endpoint_type& _remote,
        boost::asio::io_context &_io,
        const std::shared_ptr<configuration>& _configuration)
    : quic_client_endpoint_base_impl(_endpoint_host, _routing_host, _local,
                                    _remote, _io, VSOMEIP_MAX_UDP_MESSAGE_SIZE,
                                    _configuration->get_endpoint_queue_limit(
                                            _remote.address().to_string(),
                                            _remote.port()),
                                    _configuration),
      remote_address_(_remote.address()),
      remote_port_(_remote.port()),
      quic_receive_buffer_size_(_configuration->get_udp_receive_buffer_size()),
      tp_reassembler_(std::make_shared<tp::tp_reassembler>(
              _configuration->get_max_message_size_unreliable(), _io))
      //ssl(boost::asio::ssl::context{boost::asio::ssl::context::tlsv13}) 
      {
    is_supporting_someip_tp_ = true;
        }
}
#endif