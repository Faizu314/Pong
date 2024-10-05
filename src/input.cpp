#include "input.hpp"

namespace Input {

    static void ProcessKeyDownEvent(InputKeys& input, const SDL_KeyboardEvent* event) {
        if (event->repeat > 0)
            return;

        if (event->keysym.scancode == SDL_SCANCODE_UP)
            input.Up = true;
        if (event->keysym.scancode == SDL_SCANCODE_DOWN)
            input.Down = true;
        if (event->keysym.scancode == SDL_SCANCODE_LEFT)
            input.Left = true;
        if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
            input.Right = true;
        if (event->keysym.scancode == SDL_SCANCODE_SPACE)
            input.Space = true;
    }

    static void ProcessKeyUpEvent(InputKeys& input, const SDL_KeyboardEvent* event) {
        if (event->repeat > 0)
            return;

        if (event->keysym.scancode == SDL_SCANCODE_UP)
            input.Up = false;
        if (event->keysym.scancode == SDL_SCANCODE_DOWN)
            input.Down = false;
        if (event->keysym.scancode == SDL_SCANCODE_LEFT)
            input.Left = false;
        if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
            input.Right = false;
        if (event->keysym.scancode == SDL_SCANCODE_SPACE)
            input.Space = false;
    }

    void GetInput(InputKeys& input) {
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
}
