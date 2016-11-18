#pragma once
#include <string>
#include "ECSFramework/System.h"
#include "Components/TargetingComponent.h"
#include "Components/PositionComponent.h"
#include "Components/BoundingRectangleComponent.h"
#include "GameWorld/GameWorld.h"
#include "Input.h"

class PlayerTargetingSystem : public System
{
public:
	static const uint_fast64_t COMPONENTIDS = 0x00;      // No ids cause it just grabs the component
	PlayerTargetingSystem(std::string systemname, ECSManager* ecsmanager, SAS_System::Input* input, GameWorld* gameworld, std::string reticule);
	~PlayerTargetingSystem();

	uint_fast64_t ComponentBits() { return PlayerTargetingSystem::COMPONENTIDS; }    // TODO: Is this necessary or is just accessing the variable directly better?

	void ProcessEntities();
private:
	void UpdateTargetReticule();

	SAS_System::Input* _input;
	GameWorld* _gameworld;
	std::string _reticuleimage;
	uint_fast64_t _player;
	uint_fast64_t _targetreticuleid;
	TargetingComponent* _playertargetingcomponent;

};

