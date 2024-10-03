#include "application.hpp"

#ifdef _WIN32

#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    App::Run();

    return 0;
}

#elif __APPLE__

int main(int argc, const char* argv[]) {
    App::Run();
}

#endif
