#include <iostream>
#include <SDL.h>
#include "../../include/ECSFramework/ECSManager.h"
#include "../../include/SDL/SDLManager.h"
#include "../../include/Systems/InputSystem.h"
#include "../../include/Components/PositionComponent.h"
#include "../../include/Components/InputComponent.h"
#include "../../include/Components/AngleComponent.h"
#include "../../include/Components/VelocityComponent.h"
#include "../../include/Components/ShootingComponent.h"

#define MAXANGLE 90.0
#define MINANGLE -90.0
InputSystem::InputSystem(ECSManager* ECSManager, SDLManager* sdlmanager):
     ProcessingSystem(ECSManager), sdlmanager_(sdlmanager)
{

}

InputSystem::~InputSystem()
{
    //dtor
}

void InputSystem::ProcessEntity(uint_fast64_t entity)
{
    int x, y;

    // Components to use
   // PositionComponent* positioncomponent;
    AngleComponent* anglecomponent;
    ShootingComponent* shootingcomponent;
    VelocityComponent* velocitycomponent;

    // Get Relevant Component Data
   // positioncomponent = static_cast<PositionComponent*>(GetECSManager()->GetEntityComponent(entity,PositionComponent::ID));
    anglecomponent = static_cast<AngleComponent*>(GetECSManager()->GetEntityComponent(entity,AngleComponent::ID));
    shootingcomponent = static_cast<ShootingComponent*>(GetECSManager()->GetEntityComponent(entity,ShootingComponent::ID));
    velocitycomponent = static_cast<VelocityComponent*>(GetECSManager()->GetEntityComponent(entity,VelocityComponent::ID));

    mousestate_ = sdlmanager_->GetMouseState();
    keyboardstate_ = sdlmanager_->GetKeyBoardState();

    // Get Mouse State
    SDL_GetMouseState(&x,&y);
/*
    if (anglecomponent != nullptr)
    {
        double angle = (x-380)/2;

        if (angle > MAXANGLE)
            angle = MAXANGLE;
        else if (angle < MINANGLE)
            angle = MINANGLE;

        anglecomponent->SetAngle(angle);
    }

    if (shootingcomponent != nullptr)
        if (mousestate_[LEFT_MOUSEBUTTON] == true)
            shootingcomponent->Shoot(true);
*/
	// This should just flag a key press and let the movement system handle the update
	// to velocity. This currently seems way out of the scope of the InputSystem
	int velocity = 1.0 * ElapsedTime()*.25;
	velocitycomponent->SetXVelocity(0);
	if (keyboardstate_[SDL_SCANCODE_A])
		velocitycomponent->SetXVelocity(-1 * velocity);
    if (keyboardstate_[SDL_SCANCODE_D])
		velocitycomponent->SetXVelocity(velocity);
        

	velocitycomponent->SetYVelocity(0);
    if (keyboardstate_[SDL_SCANCODE_W])
		velocitycomponent->SetYVelocity(-1 * velocity);
    if (keyboardstate_[SDL_SCANCODE_S])
		velocitycomponent->SetYVelocity(velocity);


}

