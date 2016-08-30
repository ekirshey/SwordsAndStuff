#include <iostream>
#include "../../include/ECSFramework/ECSManager.h"
#include "../../include/Systems/AISystem.h"
#include "../../include/Components/AIComponent.h"
#include "../../include/Types/AITypes/AIPathing.h"
#include "../../include/Types/AITypes/AIScripted.h"

AISystem::AISystem(std::string systemname, ECSManager* ecsmanager) : ProcessingSystem(systemname, ecsmanager) {
}


AISystem::~AISystem() {
}

void AISystem::ProcessEntity(uint_fast64_t entity) {
	// Do something

	AIComponent* aicomponent = GetEntityComponent<AIComponent*>(entity, AIComponentID);

		
}