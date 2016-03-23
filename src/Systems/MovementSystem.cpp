#include <iostream>
#include "../../include/ECSFramework/ECSManager.h"
#include "../../include/Systems/MovementSystem.h"
#include "../../include/Components/PositionComponent.h"
#include "../../include/Components/VelocityComponent.h"
#include "../../include/Components/BoundingRectangleComponent.h"
#include "../../include/Components/InputComponent.h"
#include "../../include/Components/SpellCastingComponent.h"
#include "../../include/Config/ComponentDefines.h"


#include <chrono>

MovementSystem::MovementSystem(GameWorld* gameworld) : gameworld_(gameworld)
{
	SetSystemName("MovementSystem");
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
			if (spellcastingcomponent->SpellToCast() != NO_CAST && !spellcastingcomponent->Cancelable())
				canmove = false;
		}

		// Check if casting a spell, if the player is then check if the spell can be cancelled
		if (canmove) {
			int velocity = 1.0 * FrameTime()*.25;
			velocitycomponent->SetXVelocity(0);
			if (inputcomponent->Pressed(MOVE_LEFT)) {
				velocitycomponent->SetXVelocity(-1 * velocity);
				positioncomponent->SetFacing(WEST);
			}
			if (inputcomponent->Pressed(MOVE_RIGHT)) {
				velocitycomponent->SetXVelocity(velocity);
				positioncomponent->SetFacing(EAST);
			}

			velocitycomponent->SetYVelocity(0);
			if (inputcomponent->Pressed(MOVE_UP)) {
				velocitycomponent->SetYVelocity(-1 * velocity);
				positioncomponent->SetFacing(NORTH);
			}
			if (inputcomponent->Pressed(MOVE_DOWN)) {
				velocitycomponent->SetYVelocity(velocity);
				positioncomponent->SetFacing(SOUTH);
			}
		}
	}

    // Update position
    positioncomponent->SetX(positioncomponent->X() + velocitycomponent->XVelocity());
    positioncomponent->SetY(positioncomponent->Y() + velocitycomponent->YVelocity());

    boundingrectanglecomponent->SetX(boundingrectanglecomponent->X() + velocitycomponent->XVelocity());
    boundingrectanglecomponent->SetY(boundingrectanglecomponent->Y() + velocitycomponent->YVelocity());


	// Insert new coords into sparse grid
	QuadElement entitytoinsert;
	entitytoinsert.entityid = entity;
	entitytoinsert.positioncomponent = positioncomponent;
	entitytoinsert.boundingrectangle = boundingrectanglecomponent;

	if (entitytoinsert.boundingrectangle != nullptr)
		gameworld_->SparseGridInsert(entitytoinsert);

}

