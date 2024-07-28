#pragma once

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "common.hpp"
#include "renderer.hpp"

SDL_Texture* GetSpriteAsset(int spriteId);
TTF_Font* GetFontAsset(int fontId);
