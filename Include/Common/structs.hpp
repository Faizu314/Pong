#pragma once

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/ext/vector_float2.hpp>

#include "defs.hpp"

namespace Input {

    typedef struct {
        bool Up;
        bool Down;
        bool Left;
        bool Right;
        bool Space;
    } InputKeys;
}

namespace Game {

    typedef struct {
        glm::vec2 Position;
        glm::vec2 Velocity;
        SDL_Point Size;
        SDL_Texture* Texture;
    } Entity;

    typedef struct {
        SDL_Point Position;
        SDL_Rect* Selection;
        uint32_t CharCount;
        SDL_Point TextSize;
        int DynamicFontAssetId;
    } DynamicText;

    typedef struct {
        glm::vec2 PositionA;
        glm::vec2 PositionB;
    } Line;

    struct World {
        Entity HeaderText;
        DynamicText PlayerPoints;
        DynamicText ComputerPoints;
        Entity Player;
        Entity Computer;
        Entity Ball;
        Line Borders[4];

        DEV(
            DynamicText Fps;
        );
    };
}