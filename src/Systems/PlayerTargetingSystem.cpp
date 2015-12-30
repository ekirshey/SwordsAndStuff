#include <iostream>
#include <vector>
#include "../../include/Systems/PlayerTargetingSystem.h"
#include "../../include/Components/RenderComponent.h"
#include "../../include/ECSFramework/ECSManager.h"
#include "../../include/GameWorld/GameWorld.h"

// EKNOTE probably replace the reticule stop with a factory or something later
PlayerTargetingSystem::PlayerTargetingSystem(const SDLManager& sdlmanager, const GameWorld& gameworld, std::string reticule) : 
	sdlmanager_(&sdlmanager), gameworld_(&gameworld), reticuleimage_(reticule), player_(NOTARGET), targetreticuleid_(NOTARGET), playertargetingcomponent_(nullptr)
{
	SetSystemName("PlayerTargetingSystem");
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
	if (firstcreate)
	{
		SDL_Rect rect = { 0,0,26,26 };
		targetreticuleid_ = GetECSManager()->CreateEntity();
		GetECSManager()->AddComponentToEntity(targetreticuleid_, new PositionComponent(-100, -100)); // TODO MAgic numbers
		GetECSManager()->AddComponentToEntity(targetreticuleid_, new RenderComponent(reticuleimage_, rect));
		firstcreate = false;
	}

	if (playertargetingcomponent_->Target() != NOTARGET)
	{
		reticuleposition = GetEntity<PositionComponent*>(targetreticuleid_, PositionComponent::ID);
		targetposition = GetEntity<PositionComponent*>(playertargetingcomponent_->Target(), PositionComponent::ID);
		reticulerender = GetEntity<RenderComponent*>(targetreticuleid_, RenderComponent::ID);

		reticuleposition->SetX(targetposition->X());
		reticuleposition->SetY(targetposition->Y());
	}
	
	
}

void PlayerTargetingSystem::ProcessEntities()
{
	int mouseX, mouseY;
	const uint8_t* keyboardstate;
	bool* mousestate;
	BoundingRectangleComponent* targetboundingrectangle;

	// Set up Player if not already done
	if (player_ == NOTARGET)
	{
		player_ = GetECSManager()->GetAssociatedEntities("PLAYER")[0];
		playertargetingcomponent_ = GetEntity<TargetingComponent*>(player_, TargetingComponent::ID);
		playertargetingcomponent_->SetTarget(NOTARGET);
		if (playertargetingcomponent_ == nullptr)
			std::cout << "PLAYERTARGETINGSYSTEM:: No Player Targeting Component, peace out!" << std::endl;
	}

	
	mousestate = sdlmanager_->GetMouseState();
	if (mousestate[LEFT_MOUSEBUTTON] == true)
	{
		SDL_GetMouseState(&mouseX, &mouseY);
		playertargetingcomponent_->SetTarget(NOTARGET);
		playertargetingcomponent_->SetTargetState(false);

		SDL_Rect queryrect{ mouseX, mouseY, 1, 1 };
		std::vector<QuadElement> elements = gameworld_->SparseGridQueryRange(queryrect);

		for (int i = 0; i < elements.size(); i++)
		{
			if (SDL_HasIntersection(&elements[i].boundingrectangle->Rectangle(), &queryrect))
			{
				playertargetingcomponent_->SetTarget(elements[i].entityid);
				playertargetingcomponent_->SetTargetState(true);
				break;
			}
		}
		
	}

	keyboardstate = sdlmanager_->GetKeyBoardState();
	if (keyboardstate[SDL_SCANCODE_TAB])
		std::cout << "Handle Tab Targeting" << std::endl;

	if (playertargetingcomponent_->HasTarget())
		UpdateTargetReticule();

}