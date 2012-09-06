#ifndef _GMI_WLM_MESSAGE_H
#define _GMI_WLM_MESSAGE_H

#include <string>
#include <istream>
#include <boost/shared_ptr.hpp>

namespace wlm {

typedef std::vector<std::string> MessageHeader;

class Message {
private:
    MessageHeader header_;
    char* payload_;
    size_t payloadSize_;
    size_t payloadPos_;
public:
    Message() : header_(),
        payload_(NULL),
        payloadSize_(0),
        payloadPos_(0) {
    };

    ~Message() {
        delete[] payload_;
    };

    std::string& operator[](size_t p) { return header_[p]; };

    void checkPayloadSize() {
        payloadSize_ = atoi(header_[header_.size()-1].c_str());
        if ( payloadSize_ > 0 ) {
            payload_ = new char[payloadSize_];
        }
    };

    bool hasPayload() {
        return payloadSize_ > 0;
    };

    size_t getPayloadSize() {
        return payloadSize_;
    };

    MessageHeader& getHeader() {
        return header_;
    };

    char* payloadBegin() { return payload_; };
    char* payloadEnd() { return payload_ + payloadSize_; };

    size_t appendToPayload(std::istream &s) {
        size_t count = payloadSize_ - payloadPos_;
        if (count > 0) {
            count = s.readsome(payload_ + payloadPos_, count);
        }
        return count;
    };

    bool isComplete() {
        return payloadPos_ == payloadSize_;
    };

};

typedef boost::shared_ptr<Message> MessagePtr;

} // namespace wlm

#endif // _GMI_WLM_MESSAGE_H
