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

	Server(boost::asio::io_service&, const tcp::endpoint&);
	~Server();

	void handle_accept(filter_ptr&, boost::system::error_code);
	void accept_new();
private:
	boost::asio::io_service &ios_;
	tcp::acceptor acceptor_;
	std::vector<filter_ptr> filters_;
};
