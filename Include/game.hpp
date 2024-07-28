#pragma once

#include "common.hpp"
#include "asset_manager.hpp"
#include "renderer.hpp"
#include "physics.hpp"
#include "text.hpp"

void InitWorld(World& world);
void LogicTick(World& world, const Input& input, float deltaTime);
void PhysicsTick(World& world, float deltaTime);
void RenderTick(World& world);
bool HasGameStarted();
void DestroyWorld(World& world);
