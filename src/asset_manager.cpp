#include "asset_manager.hpp"

static char* _executablePath;

void InitAssetManager(char* exePath) {
    _executablePath = exePath;
}

std::string GetAssetPath(int assetId) {
    if (assetId < 0 || assetId > ASSETS_COUNT) {
        printf("Invalid spriteId");
        return std::string();
    }

    return std::string(_executablePath) + std::string(ASSET_RELATIVE_PATHS[assetId]);
}