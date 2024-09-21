#pragma once

#include <SDL2/SDL.h>

//#define DEVELOPMENT

#ifdef DEVELOPMENT
#define DEV(X) X
#else
#define DEV(X)
#endif

// SCREEN

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// BORDERS

const float BOUNDS_BOTTOM_LEFT_X = 10;
const float BOUNDS_TOP_RIGHT_X = 790;
const float BOUNDS_BOTTOM_LEFT_Y = 590;
const float BOUNDS_TOP_RIGHT_Y = 40;
const SDL_Color BORDER_COLOR = { 180, 120, 0, 255 };

// ASSETS

const int PADDLE_SPRITE = 0;
const int BALL_SPRITE = 1;
const int FONT_BITMAP_SPRITE = 2;
const int FONT_TTF = 3;

// HEADER TEXT

const int FONT_SIZE = 14;
const SDL_Color HEADER_TEXT_COLOR = { 255, 255, 255, 255 };
const SDL_Point HEADER_TEXT_RECT_CENTER = { 390, 19 };
const SDL_Point HEADER_TEXT_RECT_SIZE = { 100, 10 };

// POINTS TEXT

const SDL_Color POINTS_TEXT_COLOR = { 255, 255, 255, 255 };
const SDL_Point POINTS_TEXT_SIZE = { 12, 12 };
const SDL_Point PLAYER_POINTS_TEXT_POSITION = { 26, 16 };
const SDL_Point COMPUTER_POINTS_TEXT_POSITION = { 790 - 26, 16 };

#ifdef DEVELOPMENT

// FPS TEXT

const float FPS_TICK_DELAY = 0.5f;
const SDL_Color FPS_TEXT_COLOR = { 255, 0, 0, 255 };
const SDL_Point FPS_TEXT_SIZE = { 8, 8 };
const SDL_Point FPS_TEXT_POSITION = { 790 - 80, 590 - 16 };

#endif

// GAMEPLAY
// All speeds are in pixels per second

const float PLAYER_SPEED = 300;
const float COMPUTER_SPEED = 200;
const float BALL_SPEED = 350;

// PHYSICS
// These are factors that effect ball's angle after collision

const float REFLECTION_WEIGHT = 1.0;
const float PADDLE_DEFLECTION_WEIGHT = 1.0;
const float PADDLE_VELOCITY_WEIGHT = 1.0;
