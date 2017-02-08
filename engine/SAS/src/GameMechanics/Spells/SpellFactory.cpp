#include "GameMechanics/Spells/SpellFactory.h"
#include "ECSFramework/ECSManager.h"
#include "Types/Spell.h"

// Components
#include "Components/PositionComponent.h"
#include "Components/RenderComponent.h"
#include "Components/VelocityComponent.h"
#include "Components/BoundingRectangleComponent.h"
#include "Components/ScriptComponent.h"

void BuildRenderComponent(ECSManager* ecsmanager, uint_fast64_t summoner, uint_fast64_t spellid, const Spell& spell)
{
	SDL_Rect rect = { 0,0,16,16 };

	//ecsmanager->AddComponentToEntity<RenderComponent>(spellid, spell.graphic, rect);
}

namespace SpellFactory {

	uint_fast64_t CreateSpellEntity(ECSManager* ecsmanager, uint_fast64_t caster, const Spell& spell) {
#ifdef FOO
		uint_fast64_t spellid = ecsmanager->CreateEntity();

		spell.SetMotionComponents(ecsmanager, spellid, caster);
		//ecsmanager->AddComponentToEntity<VelocityComponent>(spellid, 0, 0 );
		BuildRenderComponent(ecsmanager, caster, spellid, spell);
		
		//ecsmanager->AddComponentToEntity<BoundingRectangleComponent>(spellid, entityposition->x_, entityposition->y_, 16, 16);
#endif
		return 0;
	}
}
