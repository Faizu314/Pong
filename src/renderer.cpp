#include "renderer.hpp"

const int SPRITE_COUNT = 3;

static SDL_Renderer* renderer;
static std::unordered_map<int, SDL_Texture*> sprites;

void InitRenderer(SDL_Window* window) {
    int renderersFlag = SDL_RENDERER_ACCELERATED;

    renderer = SDL_CreateRenderer(window, -1, renderersFlag);

    if (!renderer)
    {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        exit(1);
    }
}

void DestroyRenderer() {
    SDL_DestroyRenderer(renderer);
}

void Blit(SDL_Texture* texture, int x, int y) {
    SDL_Rect dest;
    
    dest.x = x;
    dest.y = y;
    
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void Blit(SDL_Texture* texture, SDL_Rect srcRect, int x, int y, SDL_Point size, SDL_Color tint) {
    SDL_Rect dest;
    
    dest.x = x;
    dest.y = y;
    dest.w = size.x;
    dest.h = size.y;
    
    SDL_SetTextureColorMod(texture, tint.r, tint.g, tint.b);
    SDL_RenderCopy(renderer, texture, &srcRect, &dest);
}

void DrawLine(int x1, int y1, int x2, int y2, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

SDL_Texture* LoadTexture(const char* filename) {
    SDL_Texture* texture;

    texture = IMG_LoadTexture(renderer, filename);

    if (!texture) {
        printf("Unable to load texture %s\n", filename);
    }

    return texture;
}

SDL_Texture* GetSpriteAsset(int assetId) {
    std::string assetPath = GetAssetPath(assetId);

    if (sprites.find(assetId) == sprites.end())
        sprites.insert(std::make_pair(assetId, LoadTexture(assetPath.c_str())));

    return sprites[assetId];
}

void ClearFrame() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void RenderFrame() {
    SDL_RenderPresent(renderer);
}

SDL_Point GetTextureSize(SDL_Texture* texture) {
    SDL_Point size;
    SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);
    return size;
}

SDL_Texture* GetStaticTextTexture(TTF_Font* ttfFont, const char* text) {
    SDL_Surface* surface = TTF_RenderText_Solid(ttfFont, text, HEADER_TEXT_COLOR);
    return SDL_CreateTextureFromSurface(renderer, surface);
}

void RenderEntity(const Entity& entity) {
    Blit(entity.texture, entity.position.x, entity.position.y);
}

void RenderLine(const Line& line) {
    DrawLine(line.positionA.x, line.positionA.y, line.positionB.x, line.positionB.y, BORDER_COLOR);
}

void RenderDynamicText(const DynamicText& text, SDL_Color tint) {
    int x = text.position.x;
    int y = text.position.y;
    for (uint32_t i = 0; i < text.charCount; i++) {
        Blit(text.texture, text.selection[i], x, y, text.textSize, tint);
        x += text.textSize.x;
    }
}
