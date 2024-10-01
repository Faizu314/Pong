#pragma once

#include <string>

#include "common.hpp"

namespace Assets {

	void InitAssetManager(char* execPath);
	std::string GetAssetPath(int assetId);
}