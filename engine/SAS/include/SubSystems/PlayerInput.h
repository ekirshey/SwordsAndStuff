#pragma once
#include "Components/InputComponent.h"
#include "Input.h"
#include "ECSManager.h"

class GameWorld;
class PlayerInput 
{
	public:
		PlayerInput(uint_fast64_t playerid, uint_fast64_t targetreticuleid, GameWorld* gameworld);
		void UpdateInput(ECSManager* ecs, const SAS_System::Input& input);
	private:
		void updatePlayerTarget(ECSManager* ecs, const SAS_System::Input& input);
		GameWorld* _gameworld;
		std::string _reticuleimage;
		uint_fast64_t _targetreticuleid;
		uint_fast64_t _playerid;

};
