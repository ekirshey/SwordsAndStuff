#pragma once

#include <unordered_set>
#include <vector>
#include <utility>

enum CollisionClass {COLLIDABLESPELL};

class ECSManager;
class CollisionResolver {
	public:
		CollisionResolver();
		~CollisionResolver();
		void Cleaup(ECSManager* ecs);
		void Resolve(ECSManager* ecs, uint_fast64_t entityA, uint_fast64_t entityB);
	private:
		void SpatialCollision(ECSManager* ecs, uint_fast64_t entityA, uint_fast64_t entityB);
		void DamageTransfer(ECSManager* ecs, uint_fast64_t entityA, uint_fast64_t entityB);

		std::unordered_set<uint_fast64_t> _toremove;
		std::vector<std::pair<uint_fast64_t, uint_fast64_t>> _spatial;

};