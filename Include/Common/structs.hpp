#pragma once

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/ext/vector_float2.hpp>
#include "defs.hpp"

typedef struct {
    bool Up;
    bool Down;
    bool Left;
    bool Right;
    bool Space;
} Input;

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
    SDL_Texture* Texture;
} DynamicText;

typedef struct {
    glm::vec2 PositionA;
    glm::vec2 PositionB;
} Line;

typedef struct {
    Entity HeaderText;
    DynamicText _playerPoints;
    DynamicText _computerPoints;
    Entity Player;
    Entity Computer;
    Entity Ball;
    Line Borders[4];
    
DEV(
    DynamicText Fps;
)
    
} World;
