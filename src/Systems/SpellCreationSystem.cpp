#include <iostream>
#include "../../include/ECSFramework/ECSManager.h"
#include "../../include/Systems/SpellCreationSystem.h"


SpellCreationSystem::SpellCreationSystem(ECSManager* ECSManager) : ProcessingSystem(ECSManager)
{
	SetSystemName("SpellCreationSystem");
}

SpellCreationSystem::~SpellCreationSystem()
{
	//dtor
}


void SpellCreationSystem::ProcessEntity(uint_fast64_t entity)
{
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

}