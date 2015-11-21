#include <iostream>
#include "../../include/ECSFramework/ECSManager.h"
#include "../../include/Systems/MovementSystem.h"
#include "../../include/Components/PositionComponent.h"
#include "../../include/Components/VelocityComponent.h"
#include "../../include/Components/BoundingRectangleComponent.h"
#include "../../include/Config/ComponentDefines.h"

#include <chrono>

MovementSystem::MovementSystem(ECSManager* ECSManager, GameWorld* gameworld) : ProcessingSystem(ECSManager), gameworld_(gameworld)
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
		entitytoinsert.boundingrectangle = static_cast<BoundingRectangleComponent*>(GetECSManager()->GetEntityComponent(staticobjects[i], BoundingRectangleComponentID));

		if (entitytoinsert.boundingrectangle != nullptr)
		{
			entitytoinsert.positioncomponent = static_cast<PositionComponent*>(GetECSManager()->GetEntityComponent(staticobjects[i], PositionComponentID));
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

    // Get Relevant Component Data
    positioncomponent = static_cast<PositionComponent*>(GetECSManager()->GetEntityComponent(entity,PositionComponentID));
    velocitycomponent = static_cast<VelocityComponent*>(GetECSManager()->GetEntityComponent(entity,VelocityComponentID));
    boundingrectanglecomponent = static_cast<BoundingRectangleComponent*>(GetECSManager()->GetEntityComponent(entity,BoundingRectangleComponentID));

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

