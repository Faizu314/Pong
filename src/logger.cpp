#include "logger.hpp"

#include <debugapi.h>
#include <windows.h>

void Log(const char* msg, ...) {
    va_list args;

    va_start(args, msg);

    va_end(args);

    OutputDebugString(msg);
}
