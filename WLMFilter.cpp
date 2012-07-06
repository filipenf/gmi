#include "WLMFilter.h"

using boost::asio::async_read_until;
using boost::asio::buffer;
using boost::bind;

WLMFilter::WLMFilter(boost::asio::io_service &ios) :
	socket_(ios)
{

}

void WLMFilter::start() {
	read_header();
}

void WLMFilter::read_header() {
	async_read_until(socket_, buffer(command.header()), '\n');
}

