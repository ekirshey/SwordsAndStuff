#include <iostream>
#include "../../include/ECSFramework/ECSManager.h"
#include "../../include/Systems/QuadTreeSystem.h"
#include "../../include/Components/PositionComponent.h"
#include "../../include/Components/VelocityComponent.h"
#include "../../include/Components/BoundingRectangleComponent.h"
#include "../../include/Config/ComponentDefines.h"

#include <chrono>
static int test = 0;
QuadTreeSystem::QuadTreeSystem(ECSManager* ECSManager, GameWorld* gameworld) : ProcessingSystem(ECSManager), gameworld_(gameworld)
{

}

QuadTreeSystem::~QuadTreeSystem()
{
	//dtor
}


void QuadTreeSystem::BeforeObjectProcessing()
{

	gameworld_->ClearQuadTree();
}

void QuadTreeSystem::AfterObjectProcessing()
{

}

void QuadTreeSystem::ProcessEntity(uint_fast64_t entity)
{
	QuadElement entitytoinsert;
	entitytoinsert.entityid = entity;
	entitytoinsert.positioncomponent = (static_cast<PositionComponent*>(GetECSManager()->GetEntityComponent(entity, PositionComponentID)));
	entitytoinsert.boundingrectangle = (static_cast<BoundingRectangleComponent*>(GetECSManager()->GetEntityComponent(entity, BoundingRectangleComponentID)));
	entitytoinsert.collisioncomponent = (static_cast<CollisionComponent*>(GetECSManager()->GetEntityComponent(entity, CollisionComponentID)));

	if (entitytoinsert.boundingrectangle != nullptr)
		gameworld_->Insert(entitytoinsert);


}

