#include <algorithm>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <vector>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

#include "Log.h"

using boost::asio::ip::tcp;

class GenericFilter {
public:
	GenericFilter(boost::asio::io_service& ios) :
		socket_(ios) {
	}

	tcp::socket& socket() { return socket_; };

private:
	tcp::socket socket_;
};

template <typename F>
class Server {
public:
	typedef boost::shared_ptr<F> filter_ptr;

    Server(boost::asio::io_service& s, const tcp::endpoint& e)
        : ios_(s),
        acceptor_(s, e)
    {
        accept_new();
    }

    ~Server() {
    }

    void handle_accept(filter_ptr &fp, boost::system::error_code) {
        fp->start();
        accept_new();
    }

    void accept_new() {
        LOG_FUNCTION("Server::accept_new");
        filter_ptr fp ( new F(ios_) );
        acceptor_.async_accept( fp->socket(), boost::bind(
                    &Server::handle_accept, this, fp, 
                    boost::asio::placeholders::error) );
        filters_.push_back(fp);	
    }

private:
	boost::asio::io_service &ios_;
	tcp::acceptor acceptor_;
	std::vector<filter_ptr> filters_;
};
