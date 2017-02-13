#include <iostream>
#include "PlayerInput.h"
#include "Types/MessageTypes.h"
#include "GameWorld/GameWorld.h"

PlayerInput::PlayerInput(uint_fast64_t playerid, uint_fast64_t targetreticuleid, GameWorld* gameworld)
	: _playerid(playerid)
	, _targetreticuleid(targetreticuleid)
	, _gameworld(gameworld)
{

}

void PlayerInput::updatePlayerTarget(ECSManager* ecs, const SAS_System::Input& input) {
	int x, y;
	if (input.leftMousePressed())
	{
		input.getMouseState(x, y);
		SDL_Rect queryrect{ x , y, 1, 1 };
		std::vector<QuadElement> elements;
		_gameworld->SparseGridQueryRange(queryrect, elements);

		PositionComponent* pos = ecs->GetEntityComponent<PositionComponent*>(_targetreticuleid, PositionComponentID);
		bool foundtarget = false;
		for (int i = 0; i < elements.size(); i++)
		{
			if (SDL_HasIntersection(&elements[i].boundingrectangle->Rectangle(), &queryrect))
			{
				foundtarget = true;
				pos->x_ = elements[i].positioncomponent->x_;
				pos->y_ = elements[i].positioncomponent->y_;
				break;
			}
		}

		if (!foundtarget) {
			pos->x_ = -100;
			pos->y_ = -100;
		}
	}
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

	updatePlayerTarget(ecs, input);
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
