#include "application.hpp"

#ifdef _WIN32

int WinMain(int argc, const char * argv[]) {
    RunApp();

    return 0;
}

#elif _APPLE_

int main(int argc, const char* argv[]) {
    RunApp();
}

#endif