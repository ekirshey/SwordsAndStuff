#pragma once
#include "ECSFramework/ECSManager.h"
#include "Components/PositionComponent.h"
#include "Components/ScriptComponent.h"

class SpellMotion{
	public:
		virtual void SetMotionComponents(ECSManager* ecs, uint_fast64_t id, uint_fast64_t casterid) const = 0;
};

class ScriptedMotion : public SpellMotion {
	public:
		using Script = std::vector<std::vector<ScriptStep>>;
		ScriptedMotion(Script script) 
			: _script(script)
		{
		}

		void SetMotionComponents(ECSManager* ecs, uint_fast64_t id, uint_fast64_t casterid)  const{
			PositionComponent* casterposition = ecs->GetEntityComponent<PositionComponent*>(casterid, PositionComponentID);
			PositionComponent spellposition(*casterposition);
			//Set the position to the initial scripted placement. This prevents a weird jump
			spellposition.x_ = _script[casterposition->facing_][0].dX + spellposition.x_;
			spellposition.y_ = _script[casterposition->facing_][0].dY + spellposition.y_;

			ecs->AddComponentToEntity<PositionComponent>(id, spellposition);
			ecs->AddComponentToEntity<ScriptComponent>(id, _script[casterposition->facing_], casterid);
		}
	private:
		Script _script;

};

class UnscriptedMotion : public SpellMotion {
	public:
		UnscriptedMotion(int xvelocity, int yvelocity, int lifetime) 
			: _xvelocity(xvelocity)
			, _yvelocity(yvelocity)
			, _lifetime(lifetime)
		{
		}

		void SetMotionComponents(ECSManager* ecs, uint_fast64_t id, uint_fast64_t casterid) const {

		}

	private:
		int _xvelocity;
		int _yvelocity;
		int _lifetime;
};