#include <stdio.h>

#include <boost/asio.hpp>

#include "wlm/WLMFilter.h"
#include "Server.h"

int main(int argc, char** argv) {
	boost::asio::io_service ios;

	Server<wlm::WLMFilter> server(ios, tcp::endpoint(tcp::v4(), 1863));

	ios.run();

	return 0;
}

