#include <iostream>
#include "ECSFramework/ECSManager.h"
#include "Systems/CollisionSystem.h"
#include "Components/PositionComponent.h"
#include "Components/VelocityComponent.h"
#include "Components/BoundingRectangleComponent.h"
#include "SubSystems/CollisionResolver.h"

CollisionSystem::CollisionSystem(std::string systemname, ECSManager* ecsmanager, GameWorld* gameworld) 
	: ProcessingSystem(systemname, ecsmanager)
	, _gameworld(gameworld)
{
	// Set up Collision Callback dictionary
	collisioncallbacks_[VelocityComponentID] = VelocityCollision;
	SetSystemName("CollisionSystem");
}

CollisionSystem::~CollisionSystem()
{
    //dtor
}



void CollisionSystem::ProcessEntity(uint_fast64_t entity)
{
	bool collision = false;

	// Consider a vector of commonly used components so i dont do getentitycomponent as often
	//PositionComponent*			positioncomponent  = GetEntity<PositionComponent*>(entity, PositionComponentID);
	//VelocityComponent*			velocitycomponent  = static_cast<VelocityComponent*>(entity, VelocityComponentID));
	BoundingRectangleComponent* boundingrectangle  = GetEntityComponent<BoundingRectangleComponent*>(entity, BoundingRectangleComponentID);

	std::vector<QuadElement> elements;
	// Maybe return a map with sizes and pointers to the quadelemnts vectors. That way you can avoid a slow insert call
	_gameworld->SparseGridQueryRange(boundingrectangle->Rectangle(), elements);

	for (int i = 0; i < elements.size(); i++)
	{
		if (elements[i].entityid != entity)
		{
			collision = false;
			SDL_Rect elementrect = elements[i].boundingrectangle->Rectangle();
			if (SDL_HasIntersection(&boundingrectangle->Rectangle(), &elementrect))
				_resolver.Resolve(GetECSManager(), entity, elements[i].entityid );

		}
	}
	
}


void CollisionSystem::AfterObjectProcessing() {
	_resolver.Cleaup(GetECSManager());
}

