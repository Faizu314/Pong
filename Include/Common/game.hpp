#pragma once

#include "common.hpp"
#include "renderer.hpp"
#include "physics.hpp"
#include "text.hpp"

namespace Game {

	void InitGame(SDL_Window* window);
	void LogicTick(const Input::InputKeys& input, float deltaTime);
	void PhysicsTick(float deltaTime);
	void RenderTick();
	void DestroyGame();
}