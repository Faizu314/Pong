#include "input.hpp"

namespace Input {

    static void ProcessKeyDownEvent(InputKeys& input, const SDL_KeyboardEvent* event) {
        if (event->repeat > 0)
            return;

        switch (event->keysym.scancode) {
            case SDL_SCANCODE_UP:
                input.Up = true;
                break;
            case SDL_SCANCODE_DOWN:
                input.Down = true;
                break;
            case SDL_SCANCODE_LEFT:
                input.Left = true;
                break;
            case SDL_SCANCODE_RIGHT:
                input.Right = true;
                break;
            case SDL_SCANCODE_SPACE:
                input.Space = true;
                break;
            default:
                break;
        }
    }

    static void ProcessKeyUpEvent(InputKeys& input, const SDL_KeyboardEvent* event) {
        if (event->repeat > 0)
            return;

        switch (event->keysym.scancode) {
            case SDL_SCANCODE_UP:
                input.Up = false;
                break;
            case SDL_SCANCODE_DOWN:
                input.Down = false;
                break;
            case SDL_SCANCODE_LEFT:
                input.Left = false;
                break;
            case SDL_SCANCODE_RIGHT:
                input.Right = false;
                break;
            case SDL_SCANCODE_SPACE:
                input.Space = false;
                break;
            default:
                break;
        }
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
