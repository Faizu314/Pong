#pragma once

#include "common.hpp"

namespace Game::Physics {

	void MoveEntities(World& world, float deltaTime);
	void ResolveCollision(World& world);
}