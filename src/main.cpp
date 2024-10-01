#include "platform_utils.hpp"
#include "application.hpp"

#ifdef _WIN32

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    std::string exePath = App::GetExePath(exePath);
    App::EXECUTABLE_PATH = &exePath[0];
    App::Run();

    return 0;
}

#elif __APPLE__

int main(int argc, const char* argv[]) {
    std::string exePath = App::GetExePath();
    App::EXECUTABLE_PATH = &exePath[0];
    App::Run();
}

#endif
