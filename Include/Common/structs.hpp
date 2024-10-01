#pragma once

#include <unordered_map>

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

namespace Assets {

    typedef struct {
        uint8_t x;
        uint8_t y;
    } Vector2Int;

    typedef struct {
        std::unordered_map<int, int> IndexToUnicode;
        Vector2Int CharacterSize;
        Vector2Int BitmapSize;
        SDL_Texture* Bitmap;
    } DynamicFontAsset;
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
        Assets::DynamicFontAsset* DynamicFont;
    } DynamicText;

    typedef struct {
        glm::vec2 PositionA;
        glm::vec2 PositionB;
    } Line;

    typedef struct {
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
    } World;
}
