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
    message_.reset(new Message());
	async_read_until(socket_, tempBuffer_, std::string("\r\n"),
            boost::bind(&Connection::header_handler, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
}

void Connection::header_handler(const boost::system::error_code &ec,
        std::size_t bt) {
    if ( ( ec ) || ( bt == 0 ) ) {
        read_header();
        return;
    }
    std::istream is(&tempBuffer_);
    std::string tempHeader;
    std::getline(is, tempHeader);

    boost::char_separator<char> sep(" ");
    tokenizer tokens(tempHeader, sep);
    for (tokenizer::iterator iter = tokens.begin(); iter != tokens.end(); ++iter) {
        message_->getHeader().push_back(*iter);
    }
    message_->checkPayloadSize();

    LOG(INFO) << message_->getHeader()[0] << std::endl;
    if ( message_->hasPayload() ) {
        read_payload();
    } else {
        messageReceived(message_);
        read_header();
    }
}

void Connection::write_handler(const boost::system::error_code& e) {
    if ( ! e ) {
        boost::system::error_code ignored_ec;
        socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both,
                ignored_ec);
    }
}

void Connection::read_payload() {
    LOG(INFO) << "Asking to read a payload of " << message_->getPayloadSize();
    if ( tempBuffer_.size() >= message_->getPayloadSize() ) {
    } else {
        async_read(socket_, tempBuffer_, 
            boost::bind(&Connection::payload_handler, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }
}

void Connection::payload_handler(const boost::system::error_code&,
        std::size_t) {
    if ( ! message_->isComplete() ) {
        std::istream is(&tempBuffer_);
        message_->appendToPayload(is);
    }
    if ( ! message_->isComplete() ) {
        read_payload();
    } else {
        messageReceived(message_);
        //TODO: CHECK IF HAVE SOME REMAINING DATA IN THE BUFFER - IF IT
        //IS THE CASE, WE SHOULD CHECK IF IT CONTAINS A LINE TO START
        //THE NEW MESSAGE
        read_header();
    }
}

} // namespace wlm
