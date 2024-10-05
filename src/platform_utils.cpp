#include "platform_utils.hpp"

namespace App {

#ifdef _WIN32
    
    std::string GetExePath() {
        char exePath[MAX_PATH];
        
        GetModuleFileName(nullptr, exePath, MAX_PATH);
        
        std::string formattedPath(exePath);
        std::replace(formattedPath.begin(), formattedPath.end(), '\\', '/');
        size_t lastSlash = formattedPath.find_last_of("\\/");
        
        if (lastSlash != std::string::npos)
            formattedPath = formattedPath.substr(0, lastSlash);
        
        return formattedPath;
    }
}

#elif __APPLE__
    
    std::string GetExePath() {
        char buf[PATH_MAX];
        uint32_t bufsize = PATH_MAX;
        std::string exePath;
        
        if (!_NSGetExecutablePath(buf, &bufsize)) {
            exePath = std::string(buf);
            exePath = exePath.substr(0, exePath.find_last_of("/"));
        }
        
        return exePath;
    }
}

#endif
