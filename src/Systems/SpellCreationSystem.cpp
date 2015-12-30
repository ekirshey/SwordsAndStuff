#include <iostream>
#include "../../include/ECSFramework/ECSManager.h"
#include "../../include/Systems/SpellCreationSystem.h"
#include "../../include/ECSFramework/MessageTypes.h"


SpellCreationSystem::SpellCreationSystem(MessageQueue* messagequeue) : QueueSystem(messagequeue) {
	SetSystemName("SpellCreationSystem");
	
}

SpellCreationSystem::~SpellCreationSystem() {
	//dtor
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

	EntityMessage* msg = static_cast<EntityMessage*>(data);

}