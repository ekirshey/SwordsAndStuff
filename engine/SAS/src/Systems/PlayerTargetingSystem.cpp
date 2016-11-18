#include <iostream>
#include <vector>
#include "Systems/PlayerTargetingSystem.h"
#include "Components/RenderComponent.h"
#include "ECSFramework/ECSManager.h"
#include "GameWorld/GameWorld.h"

// EKNOTE probably replace the reticule stop with a factory or something later
PlayerTargetingSystem::PlayerTargetingSystem(std::string systemname, ECSManager* ecsmanager, SAS_System::Input* input, GameWorld* gameworld, std::string reticule) :
	System(systemname, ecsmanager),
	_input(input), 
	_gameworld(gameworld), 
	_reticuleimage(reticule), 
	_player(NOTARGET), 
	_targetreticuleid(NOTARGET), 
	_playertargetingcomponent(nullptr)
{

}
	
PlayerTargetingSystem::~PlayerTargetingSystem()
{
	
}

void PlayerTargetingSystem::UpdateTargetReticule()
{
	static bool firstcreate = true;
	PositionComponent* reticuleposition;
	PositionComponent* targetposition;
	RenderComponent* reticulerender;
	SDL_Rect rect;

	// EKTEMP lame static just to move forward
	// constructor?
	if (firstcreate)
	{
		SDL_Rect rect = { 0,0,26,26 };
		_targetreticuleid = GetECSManager()->CreateEntity();
		GetECSManager()->AddComponentToEntity(_targetreticuleid, std::make_unique<PositionComponent>(-100, -100)); // TODO MAgic numbers
		GetECSManager()->AddComponentToEntity(_targetreticuleid, std::make_unique<RenderComponent>(_reticuleimage, rect, 0.0));
		firstcreate = false;
	}

	if (_playertargetingcomponent->Target() != NOTARGET)
	{
		reticuleposition = GetEntityComponent<PositionComponent*>(_targetreticuleid, PositionComponent::ID);
		targetposition = GetEntityComponent<PositionComponent*>(_playertargetingcomponent->Target(), PositionComponent::ID);
		reticulerender = GetEntityComponent<RenderComponent*>(_targetreticuleid, RenderComponent::ID);

		reticuleposition->x_ = targetposition->x_;
		reticuleposition->y_ = targetposition->y_;
	}
}

void PlayerTargetingSystem::ProcessEntities()
{
	int mouseX, mouseY;
	const uint8_t* keyboardstate;
	std::vector<bool> mousestate;
	BoundingRectangleComponent* targetboundingrectangle;

	// Set up Player if not already done
	if (_player == NOTARGET)
	{
		_player = GetECSManager()->GetAssociatedEntities("PLAYER")[0];
		_playertargetingcomponent = GetEntityComponent<TargetingComponent*>(_player, TargetingComponent::ID);
		if (_playertargetingcomponent == nullptr)
			std::cout << "PLAYERTARGETINGSYSTEM:: No Player Targeting Component, peace out!" << std::endl;
		else
			_playertargetingcomponent->SetTarget(NOTARGET);
	}

	
	if (_input->leftMousePressed())
	{
		SDL_GetMouseState(&mouseX, &mouseY);
		_playertargetingcomponent->SetTarget(NOTARGET);
		_playertargetingcomponent->SetTargetState(false);

		SDL_Rect queryrect{ mouseX, mouseY, 1, 1 };
		std::vector<QuadElement> elements = _gameworld->SparseGridQueryRange(queryrect);

		for (int i = 0; i < elements.size(); i++)
		{
			if (SDL_HasIntersection(&elements[i].boundingrectangle->Rectangle(), &queryrect))
			{
				_playertargetingcomponent->SetTarget(elements[i].entityid);
				_playertargetingcomponent->SetTargetState(true);
				break;
			}
		}
		
	}

	if (_input->isKeyPressed(SDL_SCANCODE_TAB))
		std::cout << "Handle Tab Targeting" << std::endl;

	if (_playertargetingcomponent->HasTarget())
		UpdateTargetReticule();

}