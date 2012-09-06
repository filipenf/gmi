#ifndef _GMI_WLM_FILTER_H_
#define _GMI_WLM_FILTER_H_
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

#include "WLMConnection.h"
#include "WLMMessage.h"

using boost::asio::ip::tcp;

namespace wlm {

class Filter {
private:
	boost::asio::io_service &ioService_;
    Connection client_; // the connection with internal client
    Connection server_; // keeps the conection with WLM server
    Message message_;

public:
	Filter(boost::asio::io_service &);
	void start();

    tcp::socket &socket() { return client_.socket(); };
private:
    void clientMessageReceived(MessagePtr&m);
};

} // namespace

#endif  // _GMI_WLM_FILTER_H_
