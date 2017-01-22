#pragma once
#include "Components/InputComponent.h"
#include "Input.h"

class PlayerInput 
{
	public:
		PlayerInput();
		void UpdateInput(const SAS_System::Input& input, InputComponent* playerinput);
	private:

};
