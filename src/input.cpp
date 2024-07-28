#include "input.hpp"

void ProcessKeyDownEvent(Input& input, const SDL_KeyboardEvent* event) {
    if (event->repeat > 0)
        return;

    if (event->keysym.scancode == SDL_SCANCODE_UP)
        input.up = true;
    if (event->keysym.scancode == SDL_SCANCODE_DOWN)
        input.down = true;
    if (event->keysym.scancode == SDL_SCANCODE_LEFT)
        input.left = true;
    if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
        input.right = true;
    if (event->keysym.scancode == SDL_SCANCODE_SPACE)
        input.space = true;
}

void ProcessKeyUpEvent(Input& input, const SDL_KeyboardEvent* event) {
    if (event->repeat > 0)
        return;
    
    if (event->keysym.scancode == SDL_SCANCODE_UP)
        input.up = false;
    if (event->keysym.scancode == SDL_SCANCODE_DOWN)
        input.down = false;
    if (event->keysym.scancode == SDL_SCANCODE_LEFT)
        input.left = false;
    if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
        input.right = false;
    if (event->keysym.scancode == SDL_SCANCODE_SPACE)
        input.space = false;
}

void GetInput(Input& input) {
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                exit(0);
                break;
            case SDL_KEYDOWN:
                ProcessKeyDownEvent(input, &event.key);
                break;
            case SDL_KEYUP:
                ProcessKeyUpEvent(input, &event.key);
            default:
                break;
        }
    }
}
