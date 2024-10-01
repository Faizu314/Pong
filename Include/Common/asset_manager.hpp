#pragma once

#include <string>

#include "common.hpp"
#include "text.hpp"

namespace Assets {

    void InitAssetManager(char* execPath);
    std::string GetAssetPath(int assetId);
    void DestroyAssets();
}
