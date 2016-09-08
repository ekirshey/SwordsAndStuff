#pragma once
#include <string>
#include "SDLManager.h"
#include "../ECSFramework/System.h"
#include "../../include/Components/TargetingComponent.h"
#include "../../include/Components/PositionComponent.h"
#include "../../include/Components/BoundingRectangleComponent.h"
#include "../../include/GameWorld/GameWorld.h"

class PlayerTargetingSystem : public System
{
public:
	static const uint_fast64_t COMPONENTIDS = 0x00;      // No ids cause it just grabs the component
	PlayerTargetingSystem(std::string systemname, ECSManager* ecsmanager, SAS_Rendering::SDLManager* sdlmanager, GameWorld* gameworld, std::string reticule);
	~PlayerTargetingSystem();

	uint_fast64_t ComponentBits() { return PlayerTargetingSystem::COMPONENTIDS; }    // TODO: Is this necessary or is just accessing the variable directly better?

	void ProcessEntities();
private:
	void UpdateTargetReticule();

	SAS_Rendering::SDLManager* sdlmanager_;
	GameWorld* gameworld_;
	std::string reticuleimage_;
	uint_fast64_t player_;
	uint_fast64_t targetreticuleid_;
	TargetingComponent* playertargetingcomponent_;

};
