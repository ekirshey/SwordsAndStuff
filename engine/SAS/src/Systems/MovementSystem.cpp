#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include "ECSFramework/ECSManager.h"
#include "Systems/MovementSystem.h"
#include "Components/PositionComponent.h"
#include "Components/VelocityComponent.h"
#include "Components/BoundingRectangleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SpellCastingComponent.h"
#include "Config/ComponentDefines.h"

MovementSystem::MovementSystem(std::string systemname, ECSManager* ecsmanager, GameWorld* gameworld) : 
	ProcessingSystem(systemname, ecsmanager), gameworld_(gameworld)
{

}

MovementSystem::~MovementSystem()
{
    //dtor
}


void MovementSystem::BeforeObjectProcessing()
{
	//gameworld_->ClearQuadTree();
	gameworld_->ClearSparseGrid();
}

void MovementSystem::AfterObjectProcessing()
{
	QuadElement entitytoinsert;
	// I feel like this is lame, but after updating all the moving objects I'm going to 
	// add all the static objects to the tree
	std::vector<uint_fast64_t> staticobjects = GetECSManager()->GetAssociatedEntities("STATICOBJECT");

	for (int i = 0; i < staticobjects.size(); i++)
	{
		entitytoinsert.entityid = staticobjects[i];
		entitytoinsert.boundingrectangle = GetEntityComponent<BoundingRectangleComponent*>(staticobjects[i], BoundingRectangleComponentID);

		if (entitytoinsert.boundingrectangle != nullptr)
		{
			entitytoinsert.positioncomponent = GetEntityComponent<PositionComponent*>(staticobjects[i], PositionComponentID);
			entitytoinsert.velocitycomponent = nullptr; // static objects dont have a collision component

			gameworld_->SparseGridInsert(entitytoinsert);
		}
	}
}


void MovementSystem::ProcessEntity(uint_fast64_t entity)
{
    // Components to use
    PositionComponent* positioncomponent;
    VelocityComponent* velocitycomponent;
    BoundingRectangleComponent* boundingrectanglecomponent;
	CollisionComponent* collisioncomponent;
	InputComponent* inputcomponent;
	SpellCastingComponent* spellcastingcomponent;

    // Get Relevant Component Data
    positioncomponent = GetEntityComponent<PositionComponent*>(entity,PositionComponentID);
    velocitycomponent = GetEntityComponent<VelocityComponent*>(entity,VelocityComponentID);
    boundingrectanglecomponent = GetEntityComponent<BoundingRectangleComponent*>(entity,BoundingRectangleComponentID);
	inputcomponent = GetEntityComponent<InputComponent*>(entity, InputComponentID);

	// Spells that cant be cancelled prevent movement
	spellcastingcomponent = GetEntityComponent<SpellCastingComponent*>(entity, SpellCastingComponentID);

	// This is the player so adjust his velocity based on inputs
	if (inputcomponent != nullptr)
	{
		bool canmove = true;
		if (spellcastingcomponent != nullptr) {
			if (spellcastingcomponent->spelltocast != NO_CAST && !spellcastingcomponent->cancelable)
				canmove = false;
		}

		// Check if casting a spell, if the player is then check if the spell can be cancelled
		if (canmove) {
			int velocity = 1.0 * FrameTime()*.25;
			velocitycomponent->SetXVelocity(0);
			if (inputcomponent->Pressed(MOVE_LEFT)) {
				velocitycomponent->SetXVelocity(-1 * velocity);
			}
			if (inputcomponent->Pressed(MOVE_RIGHT)) {
				velocitycomponent->SetXVelocity(velocity);
			}

			velocitycomponent->SetYVelocity(0);
			if (inputcomponent->Pressed(MOVE_UP)) {
				velocitycomponent->SetYVelocity(-1 * velocity);
			}
			if (inputcomponent->Pressed(MOVE_DOWN)) {
				velocitycomponent->SetYVelocity(velocity);
			}

			// Update angle based on mouse position
			int mx, my;
			inputcomponent->GetMousePosition(mx, my);
			double diffx = mx - positioncomponent->_x;
			double diffy = -1 * (my - positioncomponent->_y);
			double hyp = std::sqrt((diffx*diffx) + (diffy*diffy));
			// Quick performance checks show this as a minor hit. Move to lookup table if necessary
			positioncomponent->_angle = (180/M_PI)*std::atan2(diffy , diffx)*-1;
			if (positioncomponent->_angle < 0)
				positioncomponent->_angle += 360;
		}
	}

    // Update position
    positioncomponent->_x = (positioncomponent->_x + velocitycomponent->XVelocity());
    positioncomponent->_y = (positioncomponent->_y + velocitycomponent->YVelocity());

    boundingrectanglecomponent->_x = (boundingrectanglecomponent->_x + velocitycomponent->XVelocity());
    boundingrectanglecomponent->_y = (boundingrectanglecomponent->_y + velocitycomponent->YVelocity());


	// Insert new coords into sparse grid
	QuadElement entitytoinsert;
	entitytoinsert.entityid = entity;
	entitytoinsert.positioncomponent = positioncomponent;
	entitytoinsert.boundingrectangle = boundingrectanglecomponent;

	if (entitytoinsert.boundingrectangle != nullptr)
		gameworld_->SparseGridInsert(entitytoinsert);

}

