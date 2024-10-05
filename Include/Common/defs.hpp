#pragma once

#include <SDL2/SDL.h>

//#define DEVELOPMENT

#ifdef DEVELOPMENT
#define DEV(X) X
#else
#define DEV(X)
#endif

namespace Screen {

    inline const int WIDTH = 800;
    inline const int HEIGHT = 600;
}

namespace Scene {
    // BORDERS

    inline const float BOUNDS_BOTTOM_LEFT_X = 10;
    inline const float BOUNDS_TOP_RIGHT_X = 790;
    inline const float BOUNDS_BOTTOM_LEFT_Y = 590;
    inline const float BOUNDS_TOP_RIGHT_Y = 40;
    inline const SDL_Color BORDER_COLOR = { 180, 120, 0, 255 };

    // HEADER TEXT

    inline const int FONT_SIZE = 14;
    inline const SDL_Color HEADER_TEXT_COLOR = { 255, 255, 255, 255 };
    inline const SDL_Point HEADER_TEXT_RECT_CENTER = { 310, 19 };
    inline const SDL_Point HEADER_TEXT_RECT_SIZE = { 100, 10 };

    // POINTS TEXT

    inline const SDL_Color POINTS_TEXT_COLOR = { 255, 255, 255, 255 };
    inline const SDL_Point POINTS_TEXT_SIZE = { 12, 12 };
    inline const SDL_Point PLAYER_POINTS_TEXT_POSITION = { 26, 16 };
    inline const SDL_Point COMPUTER_POINTS_TEXT_POSITION = { 790 - 26, 16 };

#ifdef DEVELOPMENT

    // FPS TEXT

    inline const SDL_Color FPS_TEXT_COLOR = { 255, 0, 0, 255 };
    inline const SDL_Point FPS_TEXT_SIZE = { 8, 8 };
    inline const SDL_Point FPS_TEXT_POSITION = { 790 - 80, 590 - 16 };

#endif
}

namespace Assets {

    inline const int ASSETS_COUNT = 5;

    inline const int PADDLE_SPRITE = 0;
    inline const int BALL_SPRITE = 1;
    inline const int FONT_BITMAP_SPRITE = 2;
    inline const int FONT_TTF = 3;
    inline const int FONT_META = 4;

    inline const char* ASSET_RELATIVE_PATHS[ASSETS_COUNT] = {
        "/Assets/Sprites/Paddle.png",
        "/Assets/Sprites/Ball.png",
        "/Assets/Fonts/NullTerminator_Bitmap.png",
        "/Assets/Fonts/LiberationSans.ttf",
        "/Assets/Fonts/NullTerminator_META.xml",
    };
}

namespace Game {

    inline const int DYNAMIC_TEXT_MAX_SIZE = 256;
    
    // All speeds are in pixels per second

    inline const float PLAYER_SPEED = 300;
    inline const float COMPUTER_SPEED = 200;
    inline const float BALL_SPEED = 350;
    
#ifdef DEVELOPMENT
    
    inline const float FPS_TICK_DELAY = 0.5f;
    
#endif

    namespace Physics {

        // These are factors that effect ball's angle after collision

        inline const float REFLECTION_WEIGHT = 1.0;
        inline const float PADDLE_DEFLECTION_WEIGHT = 1.0;
        inline const float PADDLE_VELOCITY_WEIGHT = 1.0;
        
        inline const float BALL_VELOCITY_DECAY = 1.05;
    }
}

namespace Logging {
    
    inline const int LOG_BUFFER_SIZE = 256;
}
