#include "WLMFilter.h"
#include "../Log.h"

#include <istream>

using boost::asio::async_read_until;
using boost::asio::streambuf;

namespace wlm {

Filter::Filter(boost::asio::io_service &ios) :
    ioService_(ios),
	client_(ios),
    server_(ios)
{

}

void Filter::start() {
    client_.read_header();
}



}
