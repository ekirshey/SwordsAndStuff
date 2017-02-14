#pragma once
#include "Components/InputComponent.h"
#include "Input.h"
#include "ECSManager.h"

class Camera;
class GameWorld;
class PlayerInput 
{
	public:
		PlayerInput(uint_fast64_t playerid, uint_fast64_t targetreticuleid, GameWorld* gameworld);
		void UpdateInput(ECSManager* ecs,  const Camera* camera, const SAS_System::Input& input);
	private:
		void updatePlayerTarget(ECSManager* ecs, const Camera* camera, const SAS_System::Input& input);
		uint_fast64_t _playerid;
		uint_fast64_t _targetid;
		uint_fast64_t _targetreticuleid;
		bool _targetselected;
		GameWorld* _gameworld;
		int _spelltocast;
		InputComponent* _playerinput;

};
