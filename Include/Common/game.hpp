#pragma once

#include "common.hpp"
#include "renderer.hpp"
#include "physics.hpp"
#include "text.hpp"

void InitGame(SDL_Window* window);
void LogicTick(const Input& input, float deltaTime);
void PhysicsTick(float deltaTime);
void RenderTick();
bool HasGameStarted();
void DestroyGame();
