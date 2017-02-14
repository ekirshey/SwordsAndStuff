#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include <unordered_map>
#include <functional>
#include "Systems/ProcessingSystem.h"
#include "Config/CollisionCallbacks.h"
#include "Config/ComponentDefines.h"
#include "GameWorld/GameWorld.h"

class CollisionSystem : public ProcessingSystem
{
    public:
        static const uint_fast64_t COMPONENTIDS = BoundingRectangleComponentID; // just need a bounding box
        CollisionSystem(std::string systemname, ECSManager* ecsmanager, GameWorld* gameworld);
        ~CollisionSystem();

        uint_fast64_t ComponentBits() {return CollisionSystem::COMPONENTIDS;}

        void ProcessEntity(uint_fast64_t entity);
		void AfterObjectProcessing();
	private:
		std::unordered_map<uint_fast64_t, std::function<void(int, int)>> collisioncallbacks_;
		GameWorld* _gameworld;
		CollisionResolver _resolver;
};


#endif // COLLISIONSYSTEM_H
