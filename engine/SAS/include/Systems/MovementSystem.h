#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "Systems/ProcessingSystem.h"
#include "Config/ComponentDefines.h"
#include "GameWorld/GameWorld.h"

class MovementSystem : public ProcessingSystem
{
    public:
        static const uint_fast64_t COMPONENTIDS = PositionComponentID | VelocityComponentID | BoundingRectangleComponentID; 
                                                            // Unlike the component ID this can be duplicated
        MovementSystem(std::string systemname, ECSManager* ecsmanager, GameWorld* gameworld);
        ~MovementSystem();

        uint_fast64_t ComponentBits() {return MovementSystem::COMPONENTIDS;}    // TODO: Is this necessary or is just accessing the variable directly better?

        void ProcessEntity(uint_fast64_t entity);

		void BeforeObjectProcessing();
		void AfterObjectProcessing();
	private:
		GameWorld* gameworld_;
};

#endif // MOVEMENTSYSTEM_H
