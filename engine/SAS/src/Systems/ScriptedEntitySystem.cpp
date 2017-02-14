#include <iostream>
#include "Systems/ScriptedEntitySystem.h"
#include "ECSFramework/ECSManager.h"
#include "Components/ScriptComponent.h"	
#include "Components/PositionComponent.h"

ScriptedEntitySystem::ScriptedEntitySystem(std::string systemname, ECSManager* ecsmanager) :
	ProcessingSystem(systemname, ecsmanager)
{
	
}


ScriptedEntitySystem::~ScriptedEntitySystem() {

}

void ScriptedEntitySystem::ProcessEntity(uint_fast64_t entity) {

	auto script = GetEntityComponent<ScriptComponent*>(entity, ScriptComponentID);
	auto entityposition = GetEntityComponent<PositionComponent*>(entity, PositionComponentID);
	int currentstep = script->CurrentStep();

	auto steps = script->ScriptVector();

	// First pass
	if ( (currentstep == 0) && (script->StepStartTime() == 0) ) {
		script->SetStepStartTime(TimeRunning());
	}
	else if ( TimeRunning() >= (script->StepStartTime() + steps[currentstep].steplength) ) {
		script->SetStepStartTime(TimeRunning());
		script->IncCurrentStep();
		currentstep = script->CurrentStep();
	}

	if (currentstep >= steps.size()) {
		GetECSManager()->RemoveEntity(entity);
	}
	else {
		// If theres an anchor, set position to anchorpos+steppos
		// otherwise just set the position to the steppos
		if (script->GetAnchor() != -1) {
			auto anchorposition = GetEntityComponent<PositionComponent*>(script->GetAnchor(), PositionComponentID);
			if (anchorposition != nullptr) {
				entityposition->_x = anchorposition->_x + steps[currentstep].dX;
				entityposition->_y = anchorposition->_y + steps[currentstep].dY;
			}
			else
				std::cout << "Invalid script anchor " << std::endl;
		}
		else {
			entityposition->_x = steps[currentstep].dX;
			entityposition->_y = steps[currentstep].dY;
		}
	}

	
}