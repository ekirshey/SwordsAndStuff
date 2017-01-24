#include <iostream>
#include "ECSFramework/ECSManager.h"
#include "Systems/SpellCreationSystem.h"
#include "Types/MessageTypes.h"
#include "Components/SpellCastingComponent.h"
#include "Components/SpellbookComponent.h"
#include "Components/EquipmentComponent.h"
#include "GameMechanics/Spells/SpellFactory.h"

#include <Windows.h>

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
		Spell* queuedspell = spellbookcomponent->GetSpell(msg->spellId);

		if (spellcastingcomponent->SpellToCast() == NO_CAST) {
			// Check if spell is still coolingdown
			if (((TimeRunning() - queuedspell->lastcast) >= (queuedspell->cooldown + queuedspell->duration))) {
				// Check any other spell casting requirements
				spellcastingcomponent->SetSpellToCast(msg->spellId);
				spellcastingcomponent->SetCastTime(queuedspell->casttime);
				spellcastingcomponent->SetStartTimeOfCast(TimeRunning());
				spellcastingcomponent->SetCancelable(queuedspell->cancelable);
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
	Spell* spell;
	int spellid = -1;

	for (int i = castspells_.size()-1; i >= 0; i--) {

		SpellCastingComponent* spellcastingcomponent = GetEntityComponent<SpellCastingComponent*>(castspells_[i], SpellCastingComponentID);
		SpellbookComponent* spellbookcomponent = GetEntityComponent<SpellbookComponent*>(castspells_[i], SpellbookComponentID);

		castspellId = spellcastingcomponent->SpellToCast();
		spell = spellbookcomponent->GetSpell(castspellId);
		
		if (spellcastingcomponent->CastTime() <= (TimeRunning() - spellcastingcomponent->StartTimeOfCast()) ) {
			// Create spell
			spellid = SpellFactory::CreateSpellEntity(GetECSManager(), castspells_[i], *spell); 

			// Reset Spell
			spellcastingcomponent->SetSpellToCast(NO_CAST);
			spell->lastcast = TimeRunning();
			castspells_.pop_back();

		}
	}

}
