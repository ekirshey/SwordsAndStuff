#include <iostream>
#include <SDL.h>
#include "../../include/ECSFramework/ECSManager.h"
#include "../../include/SDL/SDLManager.h"
#include "../../include/Systems/InputSystem.h"
#include "../../include/Components/InputComponent.h"
#include "../../include/Types/MessageTypes.h"

//Debug
#include "../../include/Components/InventoryComponent.h"

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
    // Get Relevant Component Data
	auto inputcomponent = GetEntityComponent<InputComponent*>(entity, InputComponent::ID);

    mousestate_ = sdlmanager_->GetMouseState();
    keyboardstate_ = sdlmanager_->GetKeyBoardState();

	// Update key states
	for (auto inputid : KeyboardInputs)
	{
		if (keyboardstate_[inputcomponent->Scancode(inputid)])
		{
			if (inputcomponent->Pressed(inputid))
				inputcomponent->SetHeld(inputid, true);
			inputcomponent->SetPressed(inputid, true);
		}
		else
		{
			inputcomponent->SetHeld(inputid, false);
			inputcomponent->SetPressed(inputid, false);
		}
	}

	if (inputcomponent->Pressed(MELEE)) {
		GetECSManager()->SendMessage<MeleeMessage>("MeleeCreation", entity, 0);
	}

	// Inventory Debugging
	if (inputcomponent->Pressed(INVENTORY)) {
		auto playerinventory = GetEntityComponent<InventoryComponent*>(entity, InventoryComponent::ID);
		auto inventory = &playerinventory->inventory_;
		for (int i = 0; i < inventory->size(); i++) {
			std::cout << "ID " << inventory->at(i)->id_ << " NAME " << inventory->at(i)->GetName() << std::endl;
		}
	}


}

