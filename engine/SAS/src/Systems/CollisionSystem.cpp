#include <iostream>
#include "ECSFramework/ECSManager.h"
#include "Systems/CollisionSystem.h"
#include "Components/PositionComponent.h"
#include "Components/VelocityComponent.h"
#include "Components/BoundingRectangleComponent.h"

CollisionSystem::CollisionSystem(std::string systemname, ECSManager* ecsmanager, GameWorld* gameworld) : 
	ProcessingSystem(systemname, ecsmanager), gameworld_(gameworld)
{
	// Set up Collision Callback dictionary
	collisioncallbacks_[VelocityComponentID] = VelocityCollision;
	SetSystemName("CollisionSystem");
}

CollisionSystem::~CollisionSystem()
{
    //dtor
}

void CollisionSystem::HandleCollision(uint_fast64_t entityA, uint_fast64_t entityB)
{
	uint_fast64_t entityAcomponents = GetECSManager()->GetEntityComponentBits(entityA);
	uint_fast64_t entityBcomponents = GetECSManager()->GetEntityComponentBits(entityB);

	// At this point here we will deduce if either entity has a certain component and if it does handle its collision
	// e.g. if it has a damaging component then transfer the damage to the other entity and vice versa
	if (entityAcomponents & entityBcomponents)	// Both entity A and entity B have spatial coordinates
	{
		if (entityA != 0 && entityB != 0)
			SpatialCollision(entityA, entityB);
	}

}

void CollisionSystem::SpatialCollision(uint_fast64_t entityA, uint_fast64_t entityB)
{
	PositionComponent*			positioncomponentA  = GetEntityComponent<PositionComponent*>(entityA, PositionComponentID);
	VelocityComponent*			velocitycomponentA  = GetEntityComponent<VelocityComponent*>(entityA, VelocityComponentID);
	BoundingRectangleComponent* boundingrectangleA =  GetEntityComponent<BoundingRectangleComponent*>(entityA, BoundingRectangleComponentID);

	PositionComponent*			positioncomponentB = GetEntityComponent<PositionComponent*>(entityB, PositionComponentID);
	VelocityComponent*			velocitycomponentB = GetEntityComponent<VelocityComponent*>(entityB, VelocityComponentID);
	BoundingRectangleComponent* boundingrectangleB = GetEntityComponent<BoundingRectangleComponent*>(entityB, BoundingRectangleComponentID);

	SDL_Rect entityArect = boundingrectangleA->Rectangle();

	if (velocitycomponentA->XVelocity() != 0 && velocitycomponentA->YVelocity() != 0)
	{
		// Check which direction the collision is in
		boundingrectangleA->x_ = (boundingrectangleA->x_ - velocitycomponentA->XVelocity());
		positioncomponentA->x_ = (positioncomponentA->x_ - velocitycomponentA->XVelocity());
		if (SDL_HasIntersection(&boundingrectangleA->Rectangle(), &boundingrectangleB->Rectangle()))
		{
			boundingrectangleA->x_ = (boundingrectangleA->x_ + velocitycomponentA->XVelocity());
			positioncomponentA->x_ = (positioncomponentA->x_ + velocitycomponentA->XVelocity());

			boundingrectangleA->y_ = (boundingrectangleA->y_ - velocitycomponentA->YVelocity());
			positioncomponentA->y_ = (positioncomponentA->y_ - velocitycomponentA->YVelocity());

			if (SDL_HasIntersection(&boundingrectangleA->Rectangle(), &boundingrectangleB->Rectangle()))
			{
				boundingrectangleA->x_ = (boundingrectangleA->x_ - velocitycomponentA->XVelocity());
				positioncomponentA->x_ = (positioncomponentA->x_ - velocitycomponentA->XVelocity());
			}
		}

	}
	else
	{
		boundingrectangleA->x_ = (boundingrectangleA->x_ - velocitycomponentA->XVelocity());
		boundingrectangleA->y_ = (boundingrectangleA->y_ - velocitycomponentA->YVelocity());

		positioncomponentA->x_ = (positioncomponentA->x_ - velocitycomponentA->XVelocity());
		positioncomponentA->y_ = (positioncomponentA->y_ - velocitycomponentA->YVelocity());
	}

}

void CollisionSystem::ProcessEntity(uint_fast64_t entity)
{
	bool collision = false;

	// Consider a vector of commonly used components so i dont do getentitycomponent as often
	//PositionComponent*			positioncomponent  = GetEntity<PositionComponent*>(entity, PositionComponentID);
	//VelocityComponent*			velocitycomponent  = static_cast<VelocityComponent*>(entity, VelocityComponentID));
	BoundingRectangleComponent* boundingrectangle  = GetEntityComponent<BoundingRectangleComponent*>(entity, BoundingRectangleComponentID);

	std::vector<QuadElement> elements = gameworld_->SparseGridQueryRange(boundingrectangle->Rectangle());

	for (int i = 0; i < elements.size(); i++)
	{
		if (elements[i].entityid != entity)
		{
			collision = false;
			SDL_Rect elementrect = elements[i].boundingrectangle->Rectangle();
			if (SDL_HasIntersection(&boundingrectangle->Rectangle(), &elementrect))
				HandleCollision(entity, elements[i].entityid );

		}
	}
	
}

