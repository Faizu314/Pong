#include "renderer.hpp"

namespace Game::Renderer {

    static const int SPRITE_COUNT = 3;

    static SDL_Renderer* _renderer;
    static std::unordered_map<int, SDL_Texture*> _sprites;

    void InitRenderer(SDL_Window* window) {
        int renderersFlag = SDL_RENDERER_ACCELERATED;

        _renderer = SDL_CreateRenderer(window, -1, renderersFlag);

        if (!_renderer)
        {
            Logging::Log("Failed to create renderer: %s\n", SDL_GetError());
            exit(1);
        }
    }

    void DestroyRenderer() {
        SDL_DestroyRenderer(_renderer);
    }

    void Blit(SDL_Texture* texture, int x, int y) {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;

        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
        SDL_RenderCopy(_renderer, texture, NULL, &dest);
    }

    void Blit(SDL_Texture* texture, SDL_Rect srcRect, int x, int y, SDL_Point size, SDL_Color tint) {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        dest.w = size.x;
        dest.h = size.y;

        SDL_SetTextureColorMod(texture, tint.r, tint.g, tint.b);
        SDL_RenderCopy(_renderer, texture, &srcRect, &dest);
    }

    void DrawLine(int x1, int y1, int x2, int y2, SDL_Color color) {
        SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawLine(_renderer, x1, y1, x2, y2);
    }

    SDL_Texture* LoadTexture(const char* filename) {
        SDL_Texture* Texture;

        Texture = IMG_LoadTexture(_renderer, filename);

        if (!Texture) {
            Logging::Log("Unable to load texture %s\n", filename);
        }

        return Texture;
    }

    //Really not sure how to decouple asset management from renderer
    SDL_Texture* GetSpriteAsset(int assetId) {
        std::string assetPath = Assets::GetAssetPath(assetId);

        if (_sprites.find(assetId) == _sprites.end())
            _sprites.insert(std::make_pair(assetId, LoadTexture(assetPath.c_str())));

        return _sprites[assetId];
    }

    void ClearFrame() {
        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
        SDL_RenderClear(_renderer);
    }

    void RenderFrame() {
        SDL_RenderPresent(_renderer);
    }

    SDL_Point GetTextureSize(SDL_Texture* texture) {
        SDL_Point Size;
        SDL_QueryTexture(texture, NULL, NULL, &Size.x, &Size.y);
        return Size;
    }

    SDL_Texture* GetStaticTextTexture(TTF_Font* ttfFont, const char* text) {
        SDL_Surface* surface = TTF_RenderText_Solid(ttfFont, text, Scene::HEADER_TEXT_COLOR);
        return SDL_CreateTextureFromSurface(_renderer, surface);
    }

    void RenderEntity(const Entity& entity) {
        Blit(entity.Texture, entity.Position.x, entity.Position.y);
    }

    void RenderLine(const Line& line) {
        DrawLine(line.PositionA.x, line.PositionA.y, line.PositionB.x, line.PositionB.y, Scene::BORDER_COLOR);
    }

    void RenderDynamicText(const DynamicText& text, SDL_Color tint) {
        int x = text.Position.x;
        int y = text.Position.y;
        for (uint32_t i = 0; i < text.CharCount; i++) {
            Blit(text.DynamicFont->Bitmap, text.Selection[i], x, y, text.TextSize, tint);
            x += text.TextSize.x;
        }
    }
}
