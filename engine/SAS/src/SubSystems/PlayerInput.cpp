#include <iostream>
#include "PlayerInput.h"
#include "Types/MessageTypes.h"
#include "GameWorld/GameWorld.h"
#include "GameWorld/Camera.h"

PlayerInput::PlayerInput(uint_fast64_t playerid, uint_fast64_t targetreticuleid, GameWorld* gameworld)
	: _playerid(playerid)
	, _targetid(0)
	, _targetreticuleid(targetreticuleid)
	, _targetselected(false)
	, _gameworld(gameworld)
	, _spelltocast(0)
{

}

void PlayerInput::updatePlayerTarget(ECSManager* ecs, const Camera* camera, const SAS_System::Input& input) {
	int x, y;
	_playerinput->GetMousePosition(x, y);
	if (input.leftMouseReleased())
	{
		SDL_Rect queryrect{ x + camera->X() , y + camera->Y(), 1, 1 };
		std::vector<QuadElement> elements;
		_gameworld->SparseGridQueryRange(queryrect, elements);

		PositionComponent* pos = ecs->GetEntityComponent<PositionComponent*>(_targetreticuleid, PositionComponentID);
		_targetselected = false;
		for (int i = 0; i < elements.size(); i++)
		{
			if (SDL_HasIntersection(&elements[i].boundingrectangle->Rectangle(), &queryrect))
			{
				_targetselected = true;
				pos->_x = elements[i].positioncomponent->_x;
				pos->_y = elements[i].positioncomponent->_y;
				break;
			}
		}

		if (!_targetselected) {
			pos->_x = -100;
			pos->_y = -100;
		}
	}
	if (input.rightMouseReleased()) {
		if (_targetselected) {
			std::cout << "right click menu" << std::endl;
		}
	}

}

void PlayerInput::UpdateInput(ECSManager* ecs,  const Camera* camera, const SAS_System::Input& input) {
	int x, y;
	input.getMouseState(x, y);

	_playerinput = ecs->GetEntityComponent<InputComponent*>(_playerid, InputComponentID);

	_playerinput->SetMousePosition(x, y);

	// Update key states
	for (auto inputid : KeyboardInputs)
	{
		if (input.isKeyPressed(_playerinput->Scancode(inputid)))
		{
			if (_playerinput->Pressed(inputid))
				_playerinput->SetHeld(inputid, true);
			_playerinput->SetPressed(inputid, true);
		}
		else if(input.isKeyReleased(_playerinput->Scancode(inputid)))
		{
			_playerinput->SetHeld(inputid, false);
			_playerinput->SetPressed(inputid, false);
		}
	}
	if (_playerinput->Pressed(SELECT_SPELL0))
		_spelltocast = 0;
	else if (_playerinput->Pressed(SELECT_SPELL1))
		_spelltocast = 1;

	if (_playerinput->Pressed(MELEE)) {
		ecs->SendMessage<SpellMessage>("SpellCreation", _playerid, _spelltocast);
	}

	updatePlayerTarget(ecs, camera, input);
#ifdef FOO
	// Inventory Debugging
	if (_playerinput->Pressed(INVENTORY)) {
		auto playerinventory = ecs->GetEntityComponent<InventoryComponent*>(_playerid, InventoryComponent::ID);
		auto inventory = &playerinventory->inventor_y;
		for (int i = 0; i < inventory->size(); i++) {
			std::cout << "ID " << inventory->at(i)->id_ << " NAME " << inventory->at(i)->GetName() << std::endl;
		}
	}
#endif
}
