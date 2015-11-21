#include <iostream>
#include "../../include/Systems/PlayerTargetingSystem.h"
#include "../../include/Components/RenderComponent.h"
#include "../../include/ECSFramework/ECSManager.h"

// EKNOTE probably replace the reticule stop with a factory or something later
PlayerTargetingSystem::PlayerTargetingSystem(ECSManager* ECSManager, const SDLManager& sdlmanager, std::string reticule) : 
	System(ECSManager), sdlmanager_(&sdlmanager), reticuleimage_(reticule), player_(NOTARGET), targetreticuleid_(NOTARGET), playertargetingcomponent_(nullptr)
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
		reticuleposition = static_cast<PositionComponent*>(GetECSManager()->GetEntityComponent(targetreticuleid_, PositionComponent::ID));
		targetposition = static_cast<PositionComponent*>(GetECSManager()->GetEntityComponent(playertargetingcomponent_->Target(), PositionComponent::ID));
		reticulerender = static_cast<RenderComponent*>(GetECSManager()->GetEntityComponent(targetreticuleid_, RenderComponent::ID));

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
		std::vector<uint_fast64_t> entity = GetECSManager()->GetAssociatedEntities("PLAYER");
		if (entity.size() > 0)
		{
			player_ = GetECSManager()->GetAssociatedEntities("PLAYER")[0];
			playertargetingcomponent_ = static_cast<TargetingComponent*>(GetECSManager()->GetEntityComponent(player_, TargetingComponent::ID));
			playertargetingcomponent_->SetTarget(NOTARGET);
			if (playertargetingcomponent_ == nullptr)
				std::cout << "PLAYERTARGETINGSYSTEM:: No Player Targeting Component, peace out!" << std::endl;
		}
		else
			std::cout << "PLAYERTARGETINGSYSTEM:: No Player, should gracefully crash!" << std::endl;
	}

	
	mousestate = sdlmanager_->GetMouseState();
	if (mousestate[LEFT_MOUSEBUTTON] == true)
	{
		SDL_GetMouseState(&mouseX, &mouseY);
		std::vector<uint_fast64_t> onscreenentities = GetECSManager()->GetAssociatedEntities("ONSCREEN");
		playertargetingcomponent_->SetTarget(NOTARGET);
		playertargetingcomponent_->SetTargetState(false);
		
		for (int i = 0; i < onscreenentities.size(); i++)
		{
			targetboundingrectangle = static_cast<BoundingRectangleComponent*>
				(GetECSManager()->GetEntityComponent(onscreenentities[i], BoundingRectangleComponent::ID));
			
			if (targetboundingrectangle != nullptr)
			{
				if (( (mouseX >= targetboundingrectangle->X()) && (mouseX <= (targetboundingrectangle->X() + targetboundingrectangle->Width()))) &&
					( (mouseY >= targetboundingrectangle->Y()) && (mouseY <= (targetboundingrectangle->Y() + targetboundingrectangle->Height()))))
				{
					playertargetingcomponent_->SetTarget(onscreenentities[i]);
					playertargetingcomponent_->SetTargetState(true);
				}
			}

		}
	}

	keyboardstate = sdlmanager_->GetKeyBoardState();
	if (keyboardstate[SDL_SCANCODE_TAB])
		std::cout << "Handle Tab Targeting" << std::endl;

	if (playertargetingcomponent_->HasTarget())
		UpdateTargetReticule();

}