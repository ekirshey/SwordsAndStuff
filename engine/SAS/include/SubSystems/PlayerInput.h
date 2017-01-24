#pragma once
#include "Components/InputComponent.h"
#include "Input.h"
#include "ECSManager.h"

class PlayerInput 
{
	public:
		PlayerInput(uint64_t playerid);
		void UpdateInput(ECSManager* ecs, const SAS_System::Input& input);
	private:
		uint64_t _playerid;

};
