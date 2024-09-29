#pragma once

#include <unordered_map>
#include <cstdint>
#include <string>

#include <TinyXml/tinyxml2.h>
#include <SDL2/SDL_ttf.h>

#include "common.hpp"
#include "asset_manager.hpp"

void InitDynamicTextBitmap();
TTF_Font* GetFontAsset(int assetId);
void InitDynamicText(DynamicText& textObj, SDL_Texture* fontImage);
void SetDynamicText(DynamicText& textObj, const char* text, ...);