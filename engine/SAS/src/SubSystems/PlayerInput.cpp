#include <iostream>
#include "PlayerInput.h"
#include "Types/MessageTypes.h"

PlayerInput::PlayerInput() {
}

void PlayerInput::UpdateInput(const SAS_System::Input& input, InputComponent* playerinput) {
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
#ifdef FOO
	if (playerinput->Pressed(MELEE)) {
		GetECSManager()->SendMessage<MeleeMessage>("MeleeCreation", entity, 0);
	}

	// Inventory Debugging
	if (playerinput->Pressed(INVENTORY)) {
		auto playerinventory = GetEntityComponent<InventoryComponent*>(entity, InventoryComponent::ID);
		auto inventory = &playerinventory->inventory_;
		for (int i = 0; i < inventory->size(); i++) {
			std::cout << "ID " << inventory->at(i)->id_ << " NAME " << inventory->at(i)->GetName() << std::endl;
		}
	}
#endif

}
