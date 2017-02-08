#pragma once
#include "ECSFramework/ECSManager.h"
#include "Components/PositionComponent.h"
#include "Components/VelocityComponent.h"
#include "Components/BoundingRectangleComponent.h"
#include "Components/TTLComponent.h"

class SpellShape{
	public:
		SpellShape(int spellentities, int xvel, int yvel, int ttl)
			: _entitiestocreate(spellentities)
			, _xvel(xvel)
			, _yvel(yvel)
			, _ttl(ttl)
		{
		
		}

		// It's not unrealistic to think further dervied shape classes would be needed, so it's virtual
		virtual std::vector<uint_fast64_t> CreateSpellEntities(ECSManager* ecs, uint_fast64_t casterid, int currenttime) const {
			std::vector<uint_fast64_t> createdentities;
			for (int i = 0; i < _entitiestocreate; i++) {
				createdentities.push_back(ecs->CreateEntity());
				PositionComponent* casterposition = ecs->GetEntityComponent<PositionComponent*>(casterid, PositionComponentID);
				PositionComponent spellposition(*casterposition);
				TTLComponent ttl(_ttl, currenttime);

				VelocityComponent spellvelocity(_xvel, _yvel);
				BoundingRectangleComponent boundingrect(spellposition.x_, spellposition.y_, 16, 16);

				ecs->AddComponentToEntity<PositionComponent>(createdentities.back(), spellposition);
				ecs->AddComponentToEntity<VelocityComponent>(createdentities.back(), spellvelocity);
				ecs->AddComponentToEntity<BoundingRectangleComponent>(createdentities.back(), boundingrect);
				ecs->AddComponentToEntity<TTLComponent>(createdentities.back(), ttl);
			}

			return createdentities;
		}

	private:
		int _entitiestocreate;
		int _xvel;
		int _yvel;
		int _ttl;
};

class SpellComponent {
	public:
		virtual void SetEntityComponents(ECSManager* ecs, uint_fast64_t id, uint_fast64_t casterid) const = 0;
};

class DamageType : SpellComponent {
	
	public:
		DamageType() {}
		void SetEntityComponents(ECSManager* ecs, uint_fast64_t id, uint_fast64_t casterid) const {

		}

	private:
};
