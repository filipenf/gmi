#include <string>

class Message {
public:
    MessageHeader header;
    std::string payload;
    void checkPayloadSize() {
        payloadSize = atoi(header[header.size()-1].c_str());
    };

    bool hasPayload() {
        return payloadSize > 0;
    };

private:
    size_t payloadSize;

};

typedef std::auto_ptr<Message> MessagePtr;
