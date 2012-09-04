#include "Log.h"

void initLogging(char* v) {
    google::InitGoogleLogging(v);
    google::InstallFailureSignalHandler();
};
