#include <iostream>
#include "PlayerInput.h"
#include "Types/MessageTypes.h"

PlayerInput::PlayerInput(uint64_t playerid)
	: _playerid(playerid)
{

}

void PlayerInput::UpdateInput(ECSManager* ecs, const SAS_System::Input& input) {
	auto playerinput = ecs->GetEntityComponent<InputComponent*>(_playerid, InputComponentID);
	// Update key states
	for (auto inputid : KeyboardInputs)
	{
		if (input.isKeyPressed(playerinput->Scancode(inputid)))
		{
			if (playerinput->Pressed(inputid))
				playerinput->SetHeld(inputid, true);
			playerinput->SetPressed(inputid, true);
		}
		else if(input.isKeyReleased(playerinput->Scancode(inputid)))
		{
			playerinput->SetHeld(inputid, false);
			playerinput->SetPressed(inputid, false);
		}
	}

	if (playerinput->Pressed(MELEE)) {
		ecs->SendMessage<SpellMessage>("SpellCreation", _playerid, 0);
	}

#ifdef FOO
	// Inventory Debugging
	if (playerinput->Pressed(INVENTORY)) {
		auto playerinventory = ecs->GetEntityComponent<InventoryComponent*>(_playerid, InventoryComponent::ID);
		auto inventory = &playerinventory->inventory_;
		for (int i = 0; i < inventory->size(); i++) {
			std::cout << "ID " << inventory->at(i)->id_ << " NAME " << inventory->at(i)->GetName() << std::endl;
		}
	}
#endif
}
