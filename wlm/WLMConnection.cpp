#include "WLMConnection.h"

#include "../Log.h"

namespace wlm {

Connection::Connection(io_service &ios) : 
   ioService_(ios),
   socket_(ios) {

}

Connection::~Connection() {
}

void Connection::read_header() {
	async_read_until(socket_, tempBuffer_, std::string("\r\n"),
            boost::bind(&Connection::parse_header, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
}

void Connection::parse_header(const boost::system::error_code &ec, std::size_t bt) {
    if ( bt == 0 ) {
        read_header();
        return;
    }
    std::istream is(&tempBuffer_);
    std::string tempHeader;
    std::getline(is, tempHeader);

    boost::char_separator<char> sep(" ");
    tokenizer tokens(tempHeader, sep);
    for (tokenizer::iterator iter = tokens.begin(); iter != tokens.end(); ++iter) {
        message_.header.push_back(*iter);
    }
    message_.checkPayloadSize();

    LOG(INFO) << message_.header[0] << std::endl;
    if ( message_.hasPayload() ) {
        read_payload();
    } else {
        read_header();
    }
}

void Connection::handle_write() {
    //Write completion handler..
}

void Connection::read_payload() {
    ///TODO
}

} // namespace wlm
