#pragma once
#include "ECSFramework/ECSManager.h"
#include "Types/DamageAttributes.h"
#include "Components/DamageComponent.h"


// Make pure interface
class SpellShape{
	public:
		virtual ~SpellShape() {}

		virtual std::vector<uint_fast64_t> CreateSpellEntities(ECSManager* ecs, uint_fast64_t casterid) const = 0;
};

class XPattern : public SpellShape{
	public:
		XPattern(int vel)
			: _vel(vel)
		{
		
		}

		std::vector<uint_fast64_t> CreateSpellEntities(ECSManager* ecs, uint_fast64_t casterid) const;

	private:
		int _vel;
};

class Projectile : public SpellShape{
	public:
		Projectile(int vel)
			: _vel(vel)
		{
		
		}

		// It's not unrealistic to think further dervied shape classes would be needed, so it's virtual
		std::vector<uint_fast64_t> CreateSpellEntities(ECSManager* ecs, uint_fast64_t casterid) const;

	private:
		int _vel;
};

class SpellComponent {
	public:
		virtual void SetEntityComponents(ECSManager* ecs, uint_fast64_t id, uint_fast64_t casterid) const = 0;
};

class SpellDamage : public SpellComponent {
	
	public:
		SpellDamage(DamageAttributes attribute, double basedamage) : _damagecomponent(attribute, basedamage), _basedamage(basedamage) {}
		void SetEntityComponents(ECSManager* ecs, uint_fast64_t id, uint_fast64_t casterid) const;

	private:
		DamageComponent _damagecomponent;
		double _basedamage;

};
