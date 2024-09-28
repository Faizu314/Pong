#pragma once

#include <string>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "common.hpp"

void InitAssetManager(char* execPath);
std::string GetAssetPath(int assetId);
