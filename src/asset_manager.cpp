#include "asset_manager.hpp"

const int ASSETS_COUNT = 4;

const char* ASSET_RELATIVE_PATHS[ASSETS_COUNT] = {
    "Sprites/Paddle.png",
    "Sprites/Ball.png",
    "Fonts/NullTerminator_Bitmap.png",
    "Fonts/LiberationSans.ttf",
};

void* assetsDatabase[ASSETS_COUNT] = { nullptr };

const std::string GetAssetPath(int assetId) {
    return std::string(ASSET_PATH) + std::string(ASSET_RELATIVE_PATHS[assetId]);
}

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
    
    std::string assetPath = GetAssetPath(assetId);

    if (assetsDatabase[assetId] == nullptr)
        assetsDatabase[assetId] = LoadTexture(assetPath.c_str());
    
    return (SDL_Texture*)assetsDatabase[assetId];
}

TTF_Font* GetFontAsset(int assetId) {
    if (assetId >= ASSETS_COUNT || assetId < 0) {
        printf("Invalid spriteId");
        return nullptr;
    }
    
    std::string assetPath = GetAssetPath(assetId);

    if (assetsDatabase[assetId] == nullptr)
        assetsDatabase[assetId] = TTF_OpenFont(assetPath.c_str(), FONT_SIZE);
    
    return (TTF_Font*)assetsDatabase[assetId];
}