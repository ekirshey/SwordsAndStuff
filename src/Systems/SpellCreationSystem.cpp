#include <iostream>
#include "../../include/ECSFramework/ECSManager.h"
#include "../../include/Systems/SpellCreationSystem.h"
#include "../../include/ECSFramework/MessageTypes.h"
#include "../../include/Components/SpellCastingComponent.h"
#include "../../include/Components/SpellbookComponent.h"
#include "../../include/Components/EquipmentComponent.h"
#include "../../include/GameMechanics/Spells/SpellFactory.h"

#include <Windows.h>

SpellCreationSystem::SpellCreationSystem(MessageQueue* messagequeue) : QueueSystem(messagequeue) {
	SetSystemName("SpellCreationSystem");
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
	LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds;
	LARGE_INTEGER Frequency;

	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&StartingTime);

	// Check for valid spell message
	if (data->GetID() == SPELLMESSAGEID)// auto msg = dynamic_cast<SpellMessage*>(data))
	{
		auto msg = static_cast<SpellMessage*>(data);
		QueryPerformanceCounter(&EndingTime);
		ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
		auto spellcastingcomponent = GetEntityComponent<SpellCastingComponent*>(msg->entity, SpellCastingComponentID);
		auto spellbookcomponent = GetEntityComponent<SpellbookComponent*>(msg->entity, SpellbookComponentID);
		auto equipmentcomponent = GetEntityComponent<EquipmentComponent*>(msg->entity, EquipmentComponentID);

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

	ElapsedMicroseconds.QuadPart *= 1000000;
	ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;

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
