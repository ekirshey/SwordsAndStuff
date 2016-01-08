#include <iostream>
#include <SDL.h>
#include "../../include/ECSFramework/ECSManager.h"
#include "../../include/SDL/SDLManager.h"
#include "../../include/Systems/InputSystem.h"
#include "../../include/Components/InputComponent.h"
#include "../../include/ECSFramework/MessageTypes.h"

#define MAXANGLE 90.0
#define MINANGLE -90.0
InputSystem::InputSystem(SDLManager* sdlmanager): sdlmanager_(sdlmanager)
{
	SetSystemName("InputSystem");
}

InputSystem::~InputSystem()
{
    //dtor
}

void InputSystem::ProcessEntity(uint_fast64_t entity)
{
    int x, y;

    // Get Relevant Component Data
	auto inputcomponent = GetEntity<InputComponent*>(entity, InputComponent::ID);

    mousestate_ = sdlmanager_->GetMouseState();
    keyboardstate_ = sdlmanager_->GetKeyBoardState();

	// Update key states
	for (auto inputname : KeyboardInputs)
	{
		if (keyboardstate_[inputcomponent->Scancode(inputname)])
		{
			if (inputcomponent->Pressed(inputname))
				inputcomponent->SetHeld(inputname, true);
			inputcomponent->SetPressed(inputname, true);
		}
		else
		{
			inputcomponent->SetHeld(inputname, false);
			inputcomponent->SetPressed(inputname, false);
		}
	}

	if (inputcomponent->Pressed("MELEE"))
	{
		GetECSManager()->GetQueues().SendMessage("SpellCreation", std::unique_ptr<SpellMessage>(new SpellMessage(entity,"MELEE")));
	}



}

