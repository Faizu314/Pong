#include "application.hpp"

char* EXECUTABLE_PATH;
static SDL_Window* window;
static Input input;
static float timeScale = 1.0;

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

    window =
        SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowsFlag);

    if (!window) {
        printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
}

void Cleanup() {
    DestroyGame();
    SDL_DestroyWindow(window);
}

void InitApp() {
    InitSDL();
    InitWindow();
    InitAssetManager(EXECUTABLE_PATH);
    InitDynamicTextBitmap();
    InitGame(window);
    
    atexit(Cleanup);
}

void RunApp() {
    InitApp();
    
    Uint64 prevTime = SDL_GetPerformanceCounter();
    const double freqMs = SDL_GetPerformanceFrequency();
    double deltaTime;
    
    while (true)
    {
        GetInput(input);
        
        Uint64 currTime = SDL_GetPerformanceCounter();
        deltaTime = (currTime - prevTime) / freqMs;
        prevTime = SDL_GetPerformanceCounter();
        
DEV(
        if (input.right)
            timeScale += deltaTime;
        else if (input.left)
            timeScale -= deltaTime;
        timeScale = glm::clamp<double>(timeScale, 0.01, 10);
)
        
        LogicTick(input, deltaTime * timeScale);
        PhysicsTick(deltaTime * timeScale);
        RenderTick();
    }
}
