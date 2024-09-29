#pragma once

#include <SDL2/SDL.h>

//#define DEVELOPMENT

#ifdef DEVELOPMENT
#define DEV(X) X
#else
#define DEV(X)
#endif

namespace Screen {

    constexpr int WIDTH = 800;
    constexpr int HEIGHT = 600;
}

namespace Scene {
    // BORDERS

    constexpr float BOUNDS_BOTTOM_LEFT_X = 10;
    constexpr float BOUNDS_TOP_RIGHT_X = 790;
    constexpr float BOUNDS_BOTTOM_LEFT_Y = 590;
    constexpr float BOUNDS_TOP_RIGHT_Y = 40;
    constexpr SDL_Color BORDER_COLOR = { 180, 120, 0, 255 };

    // HEADER TEXT

    constexpr int FONT_SIZE = 14;
    constexpr SDL_Color HEADER_TEXT_COLOR = { 255, 255, 255, 255 };
    constexpr SDL_Point HEADER_TEXT_RECT_CENTER = { 390, 19 };
    constexpr SDL_Point HEADER_TEXT_RECT_SIZE = { 100, 10 };

    // POINTS TEXT

    constexpr SDL_Color POINTS_TEXT_COLOR = { 255, 255, 255, 255 };
    constexpr SDL_Point POINTS_TEXT_SIZE = { 12, 12 };
    constexpr SDL_Point PLAYER_POINTS_TEXT_POSITION = { 26, 16 };
    constexpr SDL_Point COMPUTER_POINTS_TEXT_POSITION = { 790 - 26, 16 };

#ifdef DEVELOPMENT

    // FPS TEXT

    constexpr float FPS_TICK_DELAY = 0.5f;
    constexpr SDL_Color FPS_TEXT_COLOR = { 255, 0, 0, 255 };
    constexpr SDL_Point FPS_TEXT_SIZE = { 8, 8 };
    constexpr SDL_Point FPS_TEXT_POSITION = { 790 - 80, 590 - 16 };

#endif
}

namespace Assets {

    constexpr int ASSETS_COUNT = 5;

    constexpr int PADDLE_SPRITE = 0;
    constexpr int BALL_SPRITE = 1;
    constexpr int FONT_BITMAP_SPRITE = 2;
    constexpr int FONT_TTF = 3;
    constexpr int FONT_META = 4;

    constexpr char* ASSET_RELATIVE_PATHS[ASSETS_COUNT] = {
        "/Assets/Sprites/Paddle.png",
        "/Assets/Sprites/Ball.png",
        "/Assets/Fonts/NullTerminator_Bitmap.png",
        "/Assets/Fonts/LiberationSans.ttf",
        "/Assets/Fonts/NullTerminator_META.xml",
    };
}

namespace Game {

    // All speeds are in pixels per second

    constexpr float PLAYER_SPEED = 300;
    constexpr float COMPUTER_SPEED = 200;
    constexpr float BALL_SPEED = 350;

    namespace Physics {

        // These are factors that effect ball's angle after collision

        constexpr float REFLECTION_WEIGHT = 1.0;
        constexpr float PADDLE_DEFLECTION_WEIGHT = 1.0;
        constexpr float PADDLE_VELOCITY_WEIGHT = 1.0;
    }
}
