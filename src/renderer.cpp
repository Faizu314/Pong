#include "renderer.hpp"

void Blit(SDL_Texture* texture, int x, int y) {
    SDL_Rect dest;
    
    dest.x = x;
    dest.y = y;
    
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}

void Blit(SDL_Texture* texture, SDL_Rect srcRect, int x, int y, SDL_Point size, SDL_Color tint) {
    SDL_Rect dest;
    
    dest.x = x;
    dest.y = y;
    dest.w = size.x;
    dest.h = size.y;
    
    SDL_SetTextureColorMod(texture, tint.r, tint.g, tint.b);
    SDL_RenderCopy(app.renderer, texture, &srcRect, &dest);
}

void DrawLine(int x1, int y1, int x2, int y2, SDL_Color color) {
    SDL_SetRenderDrawColor(app.renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(app.renderer, x1, y1, x2, y2);
}



void ClearFrame() {
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
    SDL_RenderClear(app.renderer);
}

void RenderFrame() {
    SDL_RenderPresent(app.renderer);
}

SDL_Point GetTextureSize(SDL_Texture* texture) {
    SDL_Point size;
    SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);
    return size;
}

SDL_Texture* GetStaticTextTexture(TTF_Font* ttfFont, const char* text) {
    SDL_Surface* surface = TTF_RenderText_Solid(ttfFont, text, HEADER_TEXT_COLOR);
    return SDL_CreateTextureFromSurface(app.renderer, surface);
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
    for (int i = 0; i < text.charCount; i++) {
        Blit(text.texture, text.selection[i], x, y, text.textSize, tint);
        x += text.textSize.x;
    }
}
