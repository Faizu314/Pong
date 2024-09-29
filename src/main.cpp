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

int main(int argc, const char* argv[]) {
    EXECUTABLE_PATH = argv[0];

    RunApp();
}

#endif
