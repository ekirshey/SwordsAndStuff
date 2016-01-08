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

	uint_fast64_t CreateSpellEntity(ECSManager* ecsmanager, uint_fast64_t summoner, const Spell& spell) {
		PositionComponent* entityposition = ecsmanager->GetEntityComponent<PositionComponent*>(summoner, PositionComponentID);
		

		uint_fast64_t spellid = ecsmanager->CreateEntity();
		ecsmanager->AddComponentToEntity<PositionComponent>(spellid, *entityposition);
		ecsmanager->AddComponentToEntity<VelocityComponent>(spellid, 0, 0 );
		BuildRenderComponent(ecsmanager, summoner, spellid, spell);

		std::vector<ScriptStep> spellscript = { ScriptStep(0,0,50), ScriptStep(-5,5,50), ScriptStep(-10,10,200) };
		ecsmanager->AddComponentToEntity<ScriptComponent>(spellid, spellscript, summoner);
		
		
		//ecsmanager->AddComponentToEntity<BoundingRectangleComponent>(spellid, entityposition->X(), entityposition->Y(), 16, 16);

		return spellid;
	}
}
