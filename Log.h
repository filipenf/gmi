#ifndef GMI_LOG_H
#define GMI_LOG_H
#include <glog/logging.h>

void initLogging(char*);

class FunctionLogger {
public:
    FunctionLogger(const char* fn) :
        functionName_(fn)
    {
        DLOG(INFO) << ">> " << functionName_;
    };

    ~FunctionLogger() {
        DLOG(INFO) << "<< " << functionName_;
    };

private:
    const char* functionName_;
};

#define LOG_FUNCTION(fn) FunctionLogger lg(fn)

#endif // GMI_LOG_H

