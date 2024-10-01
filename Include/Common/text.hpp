#pragma once

#include <unordered_map>
#include <cstdint>
#include <string>

#include <TinyXml/tinyxml2.h>
#include <SDL2/SDL_ttf.h>

#include "common.hpp"
#include "asset_manager.hpp"

namespace Assets {

	DynamicFontAsset* CreateDynamicFontAsset(SDL_Texture* bitmap, int fontMetaDataId);
    TTF_Font* GetFontAsset(int fontAssetId);
    void DestroyDynamicFonts();
}

namespace Game {

	void SetDynamicText(DynamicText& textObj, const char* text, ...);
}
