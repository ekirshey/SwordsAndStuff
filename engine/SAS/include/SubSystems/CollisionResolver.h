#pragma once

enum CollisionClass {COLLIDABLESPELL};

class ECSManager;
namespace CollisionResolver {
	void Resolve(ECSManager* ecs, uint_fast64_t entityA, uint_fast64_t entityB);

}