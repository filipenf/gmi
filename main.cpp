#include <stdio.h>

#include <boost/asio.hpp>

#include "wlm/WLMFilter.h"
#include "Server.h"
#include "Log.h"

#include <glog/logging.h>
int main(int argc, char** argv) {
    initLogging(argv[0]);
    LOG(INFO) << "Starting gmi";
	boost::asio::io_service ios;
    LOG(INFO) << "Creating wlm::Filter";
	Server<wlm::Filter> server(ios, tcp::endpoint(tcp::v4(), 1863));
    LOG(INFO) << "Starting ioservice";

	ios.run();

	return 0;
}

