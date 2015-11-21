#include <iostream>
#include "../../include/ECSFramework/ECSManager.h"
#include "../../include/Systems/CollisionSystem.h"
#include "../../include/Components/PositionComponent.h"
#include "../../include/Components/VelocityComponent.h"
#include "../../include/Components/BoundingRectangleComponent.h"

CollisionSystem::CollisionSystem(ECSManager* ECSManager, GameWorld* gameworld) : ProcessingSystem(ECSManager), gameworld_(gameworld)
{
	// Set up Collision Callback dictionary
	collisioncallbacks_[VelocityComponentID] = VelocityCollision;

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

}


void CollisionSystem::ProcessEntity(uint_fast64_t entity)
{
	bool collision = false;

	// Consider a vector of commonly used components so i dont do getentitycomponent as often
	PositionComponent*			positioncomponent  = static_cast<PositionComponent*>(GetECSManager()->GetEntityComponent(entity, PositionComponentID));
	VelocityComponent*			velocitycomponent  = static_cast<VelocityComponent*>(GetECSManager()->GetEntityComponent(entity, VelocityComponentID));
	BoundingRectangleComponent* boundingrectangle  = static_cast<BoundingRectangleComponent*>(GetECSManager()->GetEntityComponent(entity, BoundingRectangleComponentID));

	std::vector<QuadElement> elements = gameworld_->SparseGridQueryRange(boundingrectangle->Rectangle());
	
	for (int i = 0; i < elements.size(); i++)
	{
		if (elements[i].entityid != entity)
		{
			collision = false;
			SDL_Rect elementrect = elements[i].boundingrectangle->Rectangle();
			if (SDL_HasIntersection(&boundingrectangle->Rectangle(), &elementrect))
			{
				SDL_Rect entityrect = boundingrectangle->Rectangle();
				collision = true;
				if (velocitycomponent->XVelocity() != 0 && velocitycomponent->YVelocity() != 0)
				{
					// Check which direction the collision is in
					boundingrectangle->SetX(boundingrectangle->X() - velocitycomponent->XVelocity());
					positioncomponent->SetX(positioncomponent->X() - velocitycomponent->XVelocity());
					if (SDL_HasIntersection(&boundingrectangle->Rectangle(), &elementrect))
					{
						boundingrectangle->SetX(boundingrectangle->X() + velocitycomponent->XVelocity());
						positioncomponent->SetX(positioncomponent->X() + velocitycomponent->XVelocity());

						boundingrectangle->SetY(boundingrectangle->Y() - velocitycomponent->YVelocity());
						positioncomponent->SetY(positioncomponent->Y() - velocitycomponent->YVelocity());

						if (SDL_HasIntersection(&boundingrectangle->Rectangle(), &elementrect))
						{						
							boundingrectangle->SetX(boundingrectangle->X() - velocitycomponent->XVelocity());
							positioncomponent->SetX(positioncomponent->X() - velocitycomponent->XVelocity());							
						}
					}
					
				}
				else
				{
					boundingrectangle->SetX(boundingrectangle->X() - velocitycomponent->XVelocity());
					boundingrectangle->SetY(boundingrectangle->Y() - velocitycomponent->YVelocity());

					positioncomponent->SetX(positioncomponent->X() - velocitycomponent->XVelocity());
					positioncomponent->SetY(positioncomponent->Y() - velocitycomponent->YVelocity());
				}

			}

		}
	}
	

}

