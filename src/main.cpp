#include "application.hpp"

#ifdef _WIN32

#include <windows.h>
#include <algorithm>

std::string FormatExePath(const char* moduleFileName) {
    std::string formattedPath(moduleFileName);
    std::replace(formattedPath.begin(), formattedPath.end(), '\\', '/');
    size_t lastSlash = formattedPath.find_last_of("\\/");
    if (lastSlash != std::string::npos)
        formattedPath = formattedPath.substr(0, lastSlash);
    
    return formattedPath;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    char exePath[MAX_PATH];

    GetModuleFileName(hInstance, exePath, MAX_PATH);
    std::string path = FormatExePath(exePath);

    App::EXECUTABLE_PATH = &path[0];
    App::Run();

    return 0;
}

#elif __APPLE__

#include <mach-o/dyld.h>
#include <limits.h>

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

int main(int argc, const char* argv[]) {
    std::string exePath = GetExePath();
    
    App::EXECUTABLE_PATH = &exePath[0];
    App::Run();
}

#endif
