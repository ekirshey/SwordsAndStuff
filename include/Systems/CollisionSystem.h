#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include <unordered_map>
#include <functional>
#include "../Systems/ProcessingSystem.h"
#include "../Config/CollisionCallbacks.h"
#include "../Config/ComponentDefines.h"
#include "../GameWorld/GameWorld.h"

class CollisionSystem : public ProcessingSystem
{
    public:
        static const uint_fast64_t COMPONENTIDS = BoundingRectangleComponentID; // just need a bounding box
        CollisionSystem(ECSManager* ECSManager, GameWorld* gameworld);
        ~CollisionSystem();

        uint_fast64_t ComponentBits() {return CollisionSystem::COMPONENTIDS;}

        void ProcessEntity(uint_fast64_t entity);
	private:
		void HandleCollision(uint_fast64_t entityA, uint_fast64_t entityB);
		std::unordered_map<uint_fast64_t, std::function<void(int, int)>> collisioncallbacks_;

		void SpatialCollision(uint_fast64_t entityA, uint_fast64_t entityB);

		GameWorld* gameworld_;
};


#endif // COLLISIONSYSTEM_H
