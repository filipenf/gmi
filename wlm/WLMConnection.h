#ifndef _GMI_WLM_CONNECTION_H_
#define _GMI_WLM_CONNECTION_H_

#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/tokenizer.hpp>

using boost::asio::ip::tcp;
using boost::asio::io_service;

namespace wlm {

typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

class Connection {
public:
    Connection(io_service &ios);
    ~Connection();

    tcp::socket& socket() { return socket_; };

	void read_header();
    void read_payload();
    void handle_write();
    void parse_header(const boost::system::error_code&, std::size_t);
private:
    io_service &ioService_;
    tcp::socket socket_;
    boost::asio::streambuf tempBuffer_;
};

} // namespace wlm

#endif  // _GMI_WLM_CONNECTION_H_
