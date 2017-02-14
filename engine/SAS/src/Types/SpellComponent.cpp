#include <math.h>
#include "SpellComponent.h"
#include "Components/PositionComponent.h"
#include "Components/VelocityComponent.h"
#include "Components/BoundingRectangleComponent.h"
#include "Components/CollisionComponent.h"
#include "Components/RenderComponent.h"

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
		BoundingRectangleComponent boundingrect(spellposition._x, spellposition._y, 16, 16);

		ecs->AddComponentToEntity<PositionComponent>(createdentities.back(), spellposition);
		ecs->AddComponentToEntity<VelocityComponent>(createdentities.back(), spellvelocity);
		ecs->AddComponentToEntity<BoundingRectangleComponent>(createdentities.back(), boundingrect);
		ecs->AddComponentToEntity<CollisionComponent>(createdentities.back(), CollisionComponent{ COLLIDABLESPELL, casterid });
		ct++;
	}

	return createdentities;
}


std::vector<uint_fast64_t> Projectile::CreateSpellEntities(ECSManager* ecs, uint_fast64_t casterid) const {
	std::vector<uint_fast64_t> createdentities;
	createdentities.push_back(ecs->CreateEntity());
	PositionComponent* casterposition = ecs->GetEntityComponent<PositionComponent*>(casterid, PositionComponentID);
	RenderComponent* casterrender = ecs->GetEntityComponent<RenderComponent*>(casterid, RenderComponentID);
	// Offset so spell is spawned at center of caster
	PositionComponent spellposition(casterposition->_x + casterrender->ClipRect().w/2 - 8, casterposition->_y - casterrender->ClipRect().h + 16, casterposition->_angle);
	BoundingRectangleComponent boundingrect(spellposition._x, spellposition._y, 16, 16);

	double xvel = std::cos((M_PI/180)*casterposition->_angle)*_vel;
	double yvel = std::sin((M_PI/180)*casterposition->_angle)*_vel;

	ecs->AddComponentToEntity<VelocityComponent>(createdentities.back(), VelocityComponent(xvel, yvel));

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