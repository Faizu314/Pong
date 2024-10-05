#pragma once

#include "defs.hpp"
#include <iostream>

#if _WIN32

#include <windows.h>

#endif

namespace Logging {
    
    void Log(const char* msg, ...);
}
