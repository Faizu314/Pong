#include "application.hpp"

App app;
World world;
Input input;
float timeScale = 1.0;

void InitSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
    
    int renderersFlag, windowsFlag = 0;
    
    app.window = 
        SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowsFlag);
    
    if (!app.window) {
        printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
        exit(1);
    }
    
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    
    renderersFlag = SDL_RENDERER_ACCELERATED;
    
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    
    app.renderer = SDL_CreateRenderer(app.window, -1, renderersFlag);
    
    if (!app.renderer)
    {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        exit(1);
    }
    
    if (TTF_Init() < 0) {
        printf("Failed to init TTF: %s\n", SDL_GetError());
        exit(1);
    }
}

void Cleanup() {
    DestroyWorld(world);
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
}

void InitApp() {
    memset(&app, 0, sizeof(app));
    
    InitSDL();
    InitDynamicTextBitmap();
    InitWorld(world);
    
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
        
        LogicTick(world, input, deltaTime * timeScale);
        PhysicsTick(world, deltaTime * timeScale);
        RenderTick(world);
    }
}
