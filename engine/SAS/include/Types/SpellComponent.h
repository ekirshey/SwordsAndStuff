#pragma once
#include "ECSFramework/ECSManager.h"
#include "Components/PositionComponent.h"
#include "Components/VelocityComponent.h"
#include "Components/BoundingRectangleComponent.h"
// Make pure interface
class SpellShape{
	public:
		virtual ~SpellShape() {}

		virtual std::vector<uint_fast64_t> CreateSpellEntities(ECSManager* ecs, uint_fast64_t casterid) const = 0;
};

class XShape : public SpellShape{
	public:
		XShape(int vel)
			: _vel(vel)
		{
		
		}

		// It's not unrealistic to think further dervied shape classes would be needed, so it's virtual
		virtual std::vector<uint_fast64_t> CreateSpellEntities(ECSManager* ecs, uint_fast64_t casterid) const {
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

	private:
		int _vel;
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
