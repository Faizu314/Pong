#pragma once

#include "common.hpp"

namespace Game::Physics {

	void MoveEntities(World& world, float deltaTime);
	void ResolveCollisions(World& world);
}
