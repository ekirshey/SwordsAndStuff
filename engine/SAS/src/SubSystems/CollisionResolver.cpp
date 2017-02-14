#include "ECSManager.h"
#include "SubSystems/CollisionResolver.h"
#include "Components/PositionComponent.h"
#include "Components/VelocityComponent.h"
#include "Components/BoundingRectangleComponent.h"
#include "Components/DamageComponent.h"
#include "Components/CollisionComponent.h"
#include "Components/StatsComponent.h"

CollisionResolver::CollisionResolver() {}
CollisionResolver::~CollisionResolver() {}

void CollisionResolver::SpatialCollision(ECSManager* ecs, uint_fast64_t entityA, uint_fast64_t entityB)
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
		boundA->_x = (boundA->_x - velA->XVelocity());
		posA->_x = (posA->_x - velA->XVelocity());
		if (SDL_HasIntersection(&boundA->Rectangle(), &boundB->Rectangle()))
		{
			boundA->_x = (boundA->_x + velA->XVelocity());
			posA->_x = (posA->_x + velA->XVelocity());

			boundA->_y = (boundA->_y - velA->YVelocity());
			posA->_y = (posA->_y - velA->YVelocity());

			if (SDL_HasIntersection(&boundA->Rectangle(), &boundB->Rectangle()))
			{
				boundA->_x = (boundA->_x - velA->XVelocity());
				posA->_x = (posA->_x - velA->XVelocity());
			}
		}

	}
	else
	{
		boundA->_x = (boundA->_x - velA->XVelocity());
		boundA->_y = (boundA->_y - velA->YVelocity());

		posA->_x = (posA->_x - velA->XVelocity());
		posA->_y = (posA->_y - velA->YVelocity());
	}

}

// A transfers damage to B
void CollisionResolver::DamageTransfer(ECSManager* ecs, uint_fast64_t entityA, uint_fast64_t entityB) {
	DamageComponent* damage = ecs->GetEntityComponent<DamageComponent*>(entityA, DamageComponentID);
	StatsComponent* stats = ecs->GetEntityComponent<StatsComponent*>(entityB, StatsComponentID);

	stats->_derivedstats[DerivedStatType::HEALTH].currentstat -= damage->_damage;
	if (stats->_derivedstats[DerivedStatType::HEALTH].currentstat <= 0)
		_toremove.insert(entityB);
}

void CollisionResolver::Resolve(ECSManager* ecs, uint_fast64_t entityA, uint_fast64_t entityB) {
	uint_fast64_t entityAcomponents = ecs->GetEntityComponentBits(entityA);
	uint_fast64_t entityBcomponents = ecs->GetEntityComponentBits(entityB);

	CollisionComponent*			collisionA  = ecs->GetEntityComponent<CollisionComponent*>(entityA, CollisionComponentID);
	CollisionComponent*			collisionB  = ecs->GetEntityComponent<CollisionComponent*>(entityB, CollisionComponentID);
	bool aspell = (collisionA != nullptr) && collisionA->collidableclass == COLLIDABLESPELL;
	bool bspell = (collisionB != nullptr) && collisionB->collidableclass == COLLIDABLESPELL;

	// Don't handle collision if it's with the caster
	if (aspell) {
		if(collisionA->spawner == entityB)
			return;
		_toremove.insert(entityA);
	}

	if (bspell) {
		if (collisionB->spawner == entityA)
			return;
		_toremove.insert(entityB);
	}

	// I need to have a delayed handling of the spatial component. Otherwise, it moves it out of range and doesn't apply the damage
	if (entityAcomponents & entityBcomponents & BoundingRectangleComponentID)	// Both entity A and entity B have spatial coordinates
		_spatial.push_back(std::pair<uint_fast64_t, uint_fast64_t>{entityA, entityB});

	bool hasdamage = (entityAcomponents & DamageComponentID);
	bool hasstats = (entityBcomponents & StatsComponentID);
	if ( hasdamage & hasstats ) 
		DamageTransfer(ecs, entityA, entityB);

}

void CollisionResolver::Cleaup(ECSManager* ecs) {
	for (auto id : _toremove)
		ecs->RemoveEntity(id);

	for (auto pairs : _spatial)
		SpatialCollision(ecs, pairs.first, pairs.second);

	_toremove.clear();
	_spatial.clear();
}
