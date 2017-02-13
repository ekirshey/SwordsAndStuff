#include "SpellComponent.h"
#include "Components/PositionComponent.h"
#include "Components/VelocityComponent.h"
#include "Components/BoundingRectangleComponent.h"
#include "Components/CollisionComponent.h"
#include <iostream>
std::vector<uint_fast64_t> XPattern::CreateSpellEntities(ECSManager* ecs, uint_fast64_t casterid) const {
	std::vector<int> multx = { 1, 1, -1 , -1};
	std::vector<int> multy = { 1, -1 , 1, -1};
	int ct = 0;
	std::vector<uint_fast64_t> createdentities;
	for (int i = 0; i < 4; i++) {
		createdentities.push_back(ecs->CreateEntity());
		PositionComponent* casterposition = ecs->GetEntityComponent<PositionComponent*>(casterid, PositionComponentID);
		PositionComponent spellposition(*casterposition);

		VelocityComponent spellvelocity(multx[ct]*_vel, multy[ct]*_vel);
		BoundingRectangleComponent boundingrect(spellposition.x_, spellposition.y_, 16, 16);

		ecs->AddComponentToEntity<PositionComponent>(createdentities.back(), spellposition);
		ecs->AddComponentToEntity<VelocityComponent>(createdentities.back(), spellvelocity);
		ecs->AddComponentToEntity<BoundingRectangleComponent>(createdentities.back(), boundingrect);
		ct++;
	}

	return createdentities;
}


std::vector<uint_fast64_t> Projectile::CreateSpellEntities(ECSManager* ecs, uint_fast64_t casterid) const {
	std::vector<uint_fast64_t> createdentities;
	createdentities.push_back(ecs->CreateEntity());
	PositionComponent* casterposition = ecs->GetEntityComponent<PositionComponent*>(casterid, PositionComponentID);
	PositionComponent spellposition(*casterposition);
	BoundingRectangleComponent boundingrect(spellposition.x_, spellposition.y_, 16, 16);

	switch (casterposition->facing_) {
		case(NORTH):
			ecs->AddComponentToEntity<VelocityComponent>(createdentities.back(), VelocityComponent{0, -1*_vel});
			break;
		case(SOUTH):
			ecs->AddComponentToEntity<VelocityComponent>(createdentities.back(), VelocityComponent{0, _vel});
			break;
		case(EAST):
			ecs->AddComponentToEntity<VelocityComponent>(createdentities.back(), VelocityComponent{_vel, 0});
			break;
		case(WEST):
			ecs->AddComponentToEntity<VelocityComponent>(createdentities.back(), VelocityComponent{-1*_vel, 0});
			break;
		default:
			break;
	}

	ecs->AddComponentToEntity<PositionComponent>(createdentities.back(), spellposition);
	ecs->AddComponentToEntity<BoundingRectangleComponent>(createdentities.back(), boundingrect);
	ecs->AddComponentToEntity<CollisionComponent>(createdentities.back(), CollisionComponent{ COLLIDABLESPELL, casterid });

	return createdentities;
}

void SpellDamage::SetEntityComponents(ECSManager* ecs, uint_fast64_t id, uint_fast64_t casterid) const {
	// Build up some damage mods based on caster info
	// _damagecomponent._damage = *somestuff*
	ecs->AddComponentToEntity<DamageComponent>(id, _damagecomponent);

}