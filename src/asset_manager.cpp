#include "asset_manager.hpp"

namespace Assets {

    static std::string _executablePath;

    void Init() {
        _executablePath = App::GetExePath();
    }

    std::string GetAssetPath(int assetId) {
        if (assetId < 0 || assetId >= Assets::ASSETS_COUNT) {
            Logging::Log("Invalid spriteId");
            return std::string();
        }

        return _executablePath + std::string(Assets::ASSET_RELATIVE_PATHS[assetId]);
    }

    void Destroy() {
        DestroyDynamicFonts();
    }
}
