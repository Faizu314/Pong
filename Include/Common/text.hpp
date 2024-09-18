#pragma once

#include <unordered_map>
#include <cstdint>
#include <string>
#include <TinyXml/tinyxml2.h>

#include "common.hpp"
#include "asset_manager.hpp"
#include "renderer.hpp"

void InitDynamicTextBitmap();
void InitDynamicText(DynamicText& textObj);
void SetDynamicText(DynamicText& textObj, const char* text, ...);
