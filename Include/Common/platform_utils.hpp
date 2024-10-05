#pragma once

#include <string>

#ifdef _WIN32

#include <windows.h>
#include <algorithm>

#elif __APPLE__

#include <mach-o/dyld.h>
#include <limits.h>

#endif

namespace App {
    
    std::string GetExePath();
}
