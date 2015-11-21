#pragma once
#include "../Systems/ProcessingSystem.h"
#include "../Config/ComponentDefines.h"
#include "../GameWorld/GameWorld.h"

// TODO: Have movementsystem implement a class that overwrites add and remove. when an object is added it will check if it is on screen and add it to a separate vector
// ACTUALLY no, movement needs to move every single object, this is relevant for draw type systems, render etc
class QuadTreeSystem : public ProcessingSystem
{
public:
	static const uint_fast64_t COMPONENTIDS = BoundingRectangleComponentID;
	// Unlike the component ID this can be duplicated
	QuadTreeSystem(ECSManager* ECSManager, GameWorld* gameworld);
	virtual ~QuadTreeSystem();

	uint_fast64_t ComponentBits() { return QuadTreeSystem::COMPONENTIDS; }    // TODO: Is this necessary or is just accessing the variable directly better?

	void ProcessEntity(uint_fast64_t entity);

	void BeforeObjectProcessing();
	void AfterObjectProcessing();
private:
	GameWorld* gameworld_;
};

