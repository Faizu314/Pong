#pragma once

#include <unordered_map>
#include <cstdint>
#include <string>

#include <TinyXml/tinyxml2.h>
#include <SDL2/SDL_ttf.h>

#include "common.hpp"
#include "asset_manager.hpp"

namespace Assets {
    typedef struct {
        uint8_t x;
        uint8_t y;
    } Vector2Int;

    typedef struct {
        std::unordered_map<int, int> IndexToUnicode;
        Vector2Int CharacterSize;
        Vector2Int BitmapSize;
        SDL_Texture* Bitmap;
    } DynamicFontAsset;

	int CreateDynamicFontAsset(SDL_Texture* bitmap, int fontMetaDataId);
    const DynamicFontAsset* GetDynamicFontAsset(int dynamicFontAssetId);
    TTF_Font* GetFontAsset(int fontAssetId);
    void DestroyDynamicFonts();
}

namespace Game {

	void SetDynamicText(DynamicText& textObj, const char* text, ...);
}