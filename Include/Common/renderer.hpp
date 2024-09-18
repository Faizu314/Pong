#pragma once

#include <SDL2/SDL_ttf.h>

#include "common.hpp"

void ClearFrame();
void RenderFrame();
SDL_Point GetTextureSize(SDL_Texture* texture);
SDL_Texture* GetStaticTextTexture(TTF_Font* ttfFont, const char* text);
void RenderEntity(const Entity& entity);
void RenderLine(const Line& line);
void RenderDynamicText(const DynamicText& text, SDL_Color tint);
