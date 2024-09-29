#include "application.hpp"

namespace App {

    char* EXECUTABLE_PATH;

    static SDL_Window* _window;
    static Input::InputKeys _input;
    static float _timeScale = 1.0;

    void InitSDL() {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            printf("Couldn't initialize SDL: %s\n", SDL_GetError());
            exit(1);
        }

        IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

        if (TTF_Init() < 0) {
            printf("Failed to init TTF: %s\n", SDL_GetError());
            exit(1);
        }
    }

    void InitWindow() {
        int windowsFlag = 0;

        _window =
            SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Screen::WIDTH, Screen::HEIGHT, windowsFlag);

        if (!_window) {
            printf("Failed to open %d x %d window: %s\n", Screen::WIDTH, Screen::HEIGHT, SDL_GetError());
            exit(1);
        }

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    }

    void Cleanup() {
        Game::DestroyGame();
        SDL_DestroyWindow(_window);
    }

    void Init() {
        InitSDL();
        InitWindow();
        InitAssetManager(EXECUTABLE_PATH);
        Game::InitGame(_window);

        atexit(Cleanup);
    }

    void Run() {
        Init();

        Uint64 prevTime = SDL_GetPerformanceCounter();
        const double freqMs = SDL_GetPerformanceFrequency();
        double deltaTime;

        while (true)
        {
            Input::GetInput(_input);

            Uint64 currTime = SDL_GetPerformanceCounter();
            deltaTime = (currTime - prevTime) / freqMs;
            prevTime = SDL_GetPerformanceCounter();

    DEV(
            if (_input.Right)
                _timeScale += deltaTime;
            else if (_input.Left)
                _timeScale -= deltaTime;
            _timeScale = glm::clamp<double>(_timeScale, 0.01, 10);
    )

            Game::LogicTick(_input, deltaTime * _timeScale);
            Game::PhysicsTick(deltaTime * _timeScale);
            Game::RenderTick();
        }
    }
}