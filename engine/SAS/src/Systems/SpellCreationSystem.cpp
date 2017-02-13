#include <iostream>
#include "ECSFramework/ECSManager.h"
#include "Systems/SpellCreationSystem.h"
#include "Types/MessageTypes.h"
#include "Components/SpellCastingComponent.h"
#include "Components/SpellbookComponent.h"
#include "Components/EquipmentComponent.h"

/*
	Note: Not sure if this should exist in some sort of separate object outside of the ECS. I'm leaning towards it being here since it needs to update the cast
	times each loop. It's also dependent on the ECS queue system which I would need to pull out separately to move the queue type systems out. Not sure it that's
	warranted.
*/

SpellCreationSystem::SpellCreationSystem(std::string systemname, ECSManager* ecsmanager, MessageQueue* messagequeue) : 
	QueueSystem(systemname, ecsmanager, messagequeue) {

	if (messagequeue == nullptr) {
		std::cout << SystemName() << " Initialization failed! Bad queue!" << std::endl;
	}
}

SpellCreationSystem::~SpellCreationSystem() {

}


void SpellCreationSystem::ProcessMessage(Message* data) {
	/*
		Check spellcastingcomponent
			If a spell is being cast
				Is it done casting?
					Yes -> create spell
					No -> Finish processing
			If spellname contains a string/int not equal to NOCAST
				If valid spell from spellbook
					Yes -> Check if entity has appropriate resources
						Yes -> Subtract resources and update spellcasting component
						No -> Finish processing
					No -> Finish processing; throw warning
			If spellname contains NOCAST
				Finish processing
	*/
	// Check for valid spell message
	if (data->GetID() == SPELLMESSAGEID)// auto msg = dynamic_cast<SpellMessage*>(data))
	{
		auto msg = static_cast<SpellMessage*>(data);
		auto spellcastingcomponent = GetEntityComponent<SpellCastingComponent*>(msg->entity, SpellCastingComponentID);
		auto spellbookcomponent = GetEntityComponent<SpellbookComponent*>(msg->entity, SpellbookComponentID);
		auto equipmentcomponent = GetEntityComponent<EquipmentComponent*>(msg->entity, EquipmentComponentID);

		// It might need to become a copy of the spell, if I'm too apply some sort of debuff/buff. I don't want to modify the base spell
		GlobalSpellbook::SpellReference queuedspell = spellbookcomponent->GetSpell(msg->spellId);

		if (spellcastingcomponent->spelltocast == NO_CAST) {
			int lastcast = spellcastingcomponent->FindSpellLastCast(msg->spellId);
			// Check if spell is still coolingdown
			
			if (lastcast < 0 || ((TimeRunning() - lastcast) >= queuedspell->Cooldown())) {
				// Check any other spell casting requirements
				spellcastingcomponent->spelltocast = msg->spellId;
				spellcastingcomponent->casttime = queuedspell->Casttime();
				spellcastingcomponent->starttimeofcast = TimeRunning();
				spellcastingcomponent->cancelable = queuedspell->isCancelable();
				castspells_.push_back(msg->entity);

			}
		}

	}
	else {
		std::cout << "Invalid message type! Expected: SpellMessage Receieved: " << typeid(*data).name() << std::endl;
	}

	//std::cout << ElapsedMicroseconds.QuadPart << std::endl;

}

void SpellCreationSystem::AfterObjectProcessing() {
	
	int castspellId;
	GlobalSpellbook::SpellReference spell;
	int spellid = -1;

	for (int i = castspells_.size()-1; i >= 0; i--) {

		SpellCastingComponent* spellcastingcomponent = GetEntityComponent<SpellCastingComponent*>(castspells_[i], SpellCastingComponentID);
		SpellbookComponent* spellbookcomponent = GetEntityComponent<SpellbookComponent*>(castspells_[i], SpellbookComponentID);

		castspellId = spellcastingcomponent->spelltocast;
		spell = spellbookcomponent->GetSpell(castspellId);
		
		if (spellcastingcomponent->casttime <= (TimeRunning() - spellcastingcomponent->starttimeofcast) ) {
			// Create spell
			spell->CreateSpell(GetECSManager(), castspells_[i], TimeRunning());

			// Reset Spell
			spellcastingcomponent->Reset(TimeRunning());
			castspells_.pop_back();

		}
	}

}
