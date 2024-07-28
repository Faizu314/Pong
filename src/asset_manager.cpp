#include "asset_manager.hpp"

const int ASSETS_COUNT = 4;

const char* ASSET_PATHS[ASSETS_COUNT] = {
    "/Users/faizanqaiser/XCodeProjects/Pong/Pong/Sprites/Paddle.png",
    "/Users/faizanqaiser/XCodeProjects/Pong/Pong/Sprites/Ball.png",
    "/Users/faizanqaiser/XCodeProjects/Pong/Pong/Fonts/NullTerminator_Bitmap.png",
    "/Users/faizanqaiser/XCodeProjects/Pong/Pong/Fonts/LiberationSans.ttf",
};

void* assetsDatabase[ASSETS_COUNT] = { nullptr };

SDL_Texture* LoadTexture(const char* filename) {
    SDL_Texture* texture;
    
    texture = IMG_LoadTexture(app.renderer, filename);
    
    if (!texture) {
        printf("Unable to load texture %s\n", filename);
    }
    
    return texture;
}

SDL_Texture* GetSpriteAsset(int assetId) {
    if (assetId >= ASSETS_COUNT || assetId < 0) {
        printf("Invalid spriteId");
        return nullptr;
    }
    
    if (assetsDatabase[assetId] == nullptr)
        assetsDatabase[assetId] = LoadTexture(ASSET_PATHS[assetId]);
    
    return (SDL_Texture*)assetsDatabase[assetId];
}

TTF_Font* GetFontAsset(int assetId) {
    if (assetId >= ASSETS_COUNT || assetId < 0) {
        printf("Invalid spriteId");
        return nullptr;
    }
    
    if (assetsDatabase[assetId] == nullptr)
        assetsDatabase[assetId] = TTF_OpenFont(ASSET_PATHS[assetId], FONT_SIZE);
    
    return (TTF_Font*)assetsDatabase[assetId];
}
