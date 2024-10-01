#pragma once

#include <string>

#include "common.hpp"
#include "platform_utils.hpp"
#include "text.hpp"

namespace Assets {

    void InitAssetManager();
    std::string GetAssetPath(int assetId);
    void DestroyAssets();
}
