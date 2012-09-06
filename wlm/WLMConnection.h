#ifndef _GMI_WLM_CONNECTION_H_
#define _GMI_WLM_CONNECTION_H_

#include <string>
#include <boost/bind.hpp>
#include <boost/signal.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/tokenizer.hpp>

#include "WLMMessage.h"

using boost::asio::ip::tcp;
using boost::asio::io_service;

namespace wlm {

typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

typedef boost::signal<void (MessagePtr&)> OnMessageReceived;

class Connection {
public:
    Connection(io_service &ios);
    ~Connection();

    tcp::socket& socket() { return socket_; };

	void read_header();
    void read_payload();
    void write_handler(const boost::system::error_code&);
    void header_handler(const boost::system::error_code&, std::size_t);
    void payload_handler(const boost::system::error_code&, std::size_t);
    
    OnMessageReceived messageReceived;
private:
    io_service &ioService_;
    tcp::socket socket_;
    boost::asio::streambuf tempBuffer_;
    MessagePtr message_;

};

} // namespace wlm

#endif  // _GMI_WLM_CONNECTION_H_
