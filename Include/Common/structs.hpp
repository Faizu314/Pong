#pragma once

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/ext/vector_float2.hpp>
#include "defs.hpp"

typedef struct {
    bool up;
    bool down;
    bool left;
    bool right;
    bool space;
} Input;

typedef struct {
    glm::vec2 position;
    glm::vec2 velocity;
    SDL_Point size;
    SDL_Texture* texture;
} Entity;

typedef struct {
    SDL_Point position;
    SDL_Rect* selection;
    uint32_t charCount;
    SDL_Point textSize;
    SDL_Texture* texture;
} DynamicText;

typedef struct {
    glm::vec2 positionA;
    glm::vec2 positionB;
} Line;

typedef struct {
    Entity headerText;
    DynamicText playerPoints;
    DynamicText computerPoints;
    Entity player;
    Entity computer;
    Entity ball;
    Line borders[4];
    
DEV(
    DynamicText fps;
)
    
} World;
