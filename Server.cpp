#include "Server.h"

template <typename F>
Server<F>::Server(boost::asio::io_service& s, const tcp::endpoint& e)
	: ios_(s), 
	  acceptor_(s, e)
{
	accept_new();
}

template<typename F>
Server<F>::~Server() {
}

template <typename F>
void Server<F>::handle_accept(filter_ptr &fp, boost::system::error_code) {
	fp->start();
}

template <typename F>
void Server<F>::accept_new() {
	filter_ptr fp ( new F(ios_) );
	acceptor_.async_accept( fp->socket(), boost::bind(
		&Server::handle_accept, this, fp, 
		boost::asio::placeholders::error) );
	filters_.push_back(fp);	
}

