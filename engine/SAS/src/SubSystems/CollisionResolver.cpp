#include "ECSManager.h"
#include "SubSystems/CollisionResolver.h"
#include "Components/PositionComponent.h"
#include "Components/VelocityComponent.h"
#include "Components/BoundingRectangleComponent.h"
#include "Components/DamageComponent.h"
#include "Components/CollisionComponent.h"
#include "Components/StatsComponent.h"

namespace CollisionResolver {

	namespace {

		void SpatialCollision(ECSManager* ecs, uint_fast64_t entityA, uint_fast64_t entityB)
		{
			PositionComponent*			posA = ecs->GetEntityComponent<PositionComponent*>(entityA, PositionComponentID);
			VelocityComponent*			velA = ecs->GetEntityComponent<VelocityComponent*>(entityA, VelocityComponentID);
			BoundingRectangleComponent* boundA = ecs->GetEntityComponent<BoundingRectangleComponent*>(entityA, BoundingRectangleComponentID);

			PositionComponent*			posB = ecs->GetEntityComponent<PositionComponent*>(entityB, PositionComponentID);
			VelocityComponent*			velB = ecs->GetEntityComponent<VelocityComponent*>(entityB, VelocityComponentID);
			BoundingRectangleComponent* boundB = ecs->GetEntityComponent<BoundingRectangleComponent*>(entityB, BoundingRectangleComponentID);

			SDL_Rect entityArect = boundA->Rectangle();

			if (velA->XVelocity() != 0 && velA->YVelocity() != 0)
			{
				// Check which direction the collision is in
				boundA->x_ = (boundA->x_ - velA->XVelocity());
				posA->x_ = (posA->x_ - velA->XVelocity());
				if (SDL_HasIntersection(&boundA->Rectangle(), &boundB->Rectangle()))
				{
					boundA->x_ = (boundA->x_ + velA->XVelocity());
					posA->x_ = (posA->x_ + velA->XVelocity());

					boundA->y_ = (boundA->y_ - velA->YVelocity());
					posA->y_ = (posA->y_ - velA->YVelocity());

					if (SDL_HasIntersection(&boundA->Rectangle(), &boundB->Rectangle()))
					{
						boundA->x_ = (boundA->x_ - velA->XVelocity());
						posA->x_ = (posA->x_ - velA->XVelocity());
					}
				}

			}
			else
			{
				boundA->x_ = (boundA->x_ - velA->XVelocity());
				boundA->y_ = (boundA->y_ - velA->YVelocity());

				posA->x_ = (posA->x_ - velA->XVelocity());
				posA->y_ = (posA->y_ - velA->YVelocity());
			}

		}

		// A transfers damage to B
		void DamageTransfer(ECSManager* ecs, uint_fast64_t entityA, uint_fast64_t entityB) {
			DamageComponent* damage = ecs->GetEntityComponent<DamageComponent*>(entityA, DamageComponentID);
			StatsComponent* stats = ecs->GetEntityComponent<StatsComponent*>(entityB, StatsComponentID);

			stats->_derivedstats[DerivedStatType::HEALTH].currentstat -= damage->_damage;
			if (stats->_derivedstats[DerivedStatType::HEALTH].currentstat <= 0)
				ecs->RemoveEntity(entityB);
		}
	}


	void Resolve(ECSManager* ecs, uint_fast64_t entityA, uint_fast64_t entityB) {
		uint_fast64_t entityAcomponents = ecs->GetEntityComponentBits(entityA);
		uint_fast64_t entityBcomponents = ecs->GetEntityComponentBits(entityB);

		CollisionComponent*			collisionA  = ecs->GetEntityComponent<CollisionComponent*>(entityA, CollisionComponentID);
		CollisionComponent*			collisionB  = ecs->GetEntityComponent<CollisionComponent*>(entityB, CollisionComponentID);

		if ((collisionA != nullptr) && collisionA->collidableclass == COLLIDABLESPELL) {
			// Don't handle collision if it's with the caster
			if (collisionA->spawner == entityB)
				return;

			ecs->RemoveEntity(entityA);
		}

		if ((collisionB != nullptr) && collisionB->collidableclass == COLLIDABLESPELL) {
			if (collisionB->spawner == entityA)
				return;

			ecs->RemoveEntity(entityA);
		}

		// At this point here we will deduce if either entity has a certain component and if it does handle its collision
		// e.g. if it has a damaging component then transfer the damage to the other entity and vice versa
		if (entityAcomponents & entityBcomponents & BoundingRectangleComponentID)	// Both entity A and entity B have spatial coordinates
			SpatialCollision(ecs, entityA, entityB);

		bool hasdamage = (entityAcomponents & DamageComponentID);
		bool hasstats = (entityBcomponents & StatsComponentID);
		if ( hasdamage & hasstats ) 
			DamageTransfer(ecs, entityA, entityB);
	}
}