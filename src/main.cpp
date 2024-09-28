#include "application.hpp"

extern char* EXECUTABLE_PATH;

#ifdef _WIN32

#include <windows.h>
#include <algorithm>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    char exePath[MAX_PATH];

    GetModuleFileName(hInstance, exePath, MAX_PATH);

    std::string formattedpath(exePath);
    std::replace(formattedpath.begin(), formattedpath.end(), '\\', '/');
    size_t lastSlash = formattedpath.find_last_of("\\/");
    if (lastSlash != std::string::npos) {
        formattedpath = formattedpath.substr(0, lastSlash);
    }
    //formattedpath.insert(2, 1, '/');

    EXECUTABLE_PATH = &formattedpath[0];

    RunApp();

    return 0;
}

#elif __APPLE__

int main(int argc, const char* argv[]) {
    EXECUTABLE_PATH = argv[0];

    RunApp();
}

#endif
