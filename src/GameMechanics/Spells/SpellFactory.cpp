#include "../../../include/GameMechanics/Spells/SpellFactory.h"
#include "../../../include/ECSFramework/ECSManager.h"
#include "../../../include/Types/Spells.h"

// Components
#include "../../../include/Components/PositionComponent.h"
#include "../../../include/Components/RenderComponent.h"
#include "../../../include/Components/VelocityComponent.h"
#include "../../../include/Components/BoundingRectangleComponent.h"
#include "../../../include/Components/ScriptComponent.h"


void BuildRenderComponent(ECSManager* ecsmanager, uint_fast64_t summoner, uint_fast64_t spellid, const Spell& spell)
{
	SDL_Rect rect = { 0,0,16,16 };

	ecsmanager->AddComponentToEntity<RenderComponent>(spellid, spell.graphic, rect);
}

namespace SpellFactory {

	uint_fast64_t CreateSpellEntity(ECSManager* ecsmanager, uint_fast64_t caster, const Spell& spell) {
		PositionComponent* entityposition = ecsmanager->GetEntityComponent<PositionComponent*>(caster, PositionComponentID);
		

		uint_fast64_t spellid = ecsmanager->CreateEntity();
		PositionComponent spellposition(*entityposition);
		//Set the position to the initial scripted placement. This prevents a weird jump
		spellposition.x_ = spell.spellscript[entityposition->facing_][0].dX + spellposition.x_;
		spellposition.y_ = spell.spellscript[entityposition->facing_][0].dY + spellposition.y_;

		ecsmanager->AddComponentToEntity<PositionComponent>(spellid, spellposition);
		ecsmanager->AddComponentToEntity<VelocityComponent>(spellid, 0, 0 );
		BuildRenderComponent(ecsmanager, caster, spellid, spell);

		
		ecsmanager->AddComponentToEntity<ScriptComponent>(spellid, spell.spellscript[entityposition->facing_], caster);
		
		
		//ecsmanager->AddComponentToEntity<BoundingRectangleComponent>(spellid, entityposition->x_, entityposition->y_, 16, 16);

		return spellid;
	}
}
