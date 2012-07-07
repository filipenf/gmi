#include "WLMFilter.h"

using boost::asio::async_read_until;
using boost::asio::buffer;
using boost::bind;

namespace wlm {

WLMFilter::WLMFilter(boost::asio::io_service &ios) :
	io_service_(ios),
	socket_(ios)
{

}

void WLMFilter::start() {
	read_header();
}

void WLMFilter::read_header() {
	async_read_until(socket_, buffer(command.header()), '\n');
}

}
