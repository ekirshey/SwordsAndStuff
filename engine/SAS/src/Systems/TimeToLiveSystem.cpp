#pragma once
#include "TimeToLiveSystem.h"
#include "Components/TTLComponent.h"
#include "ECSManager.h"


TimeToLiveSystem::TimeToLiveSystem(std::string systemname, ECSManager* ecsmanager)
	: ProcessingSystem(systemname, ecsmanager)
{

}


TimeToLiveSystem::~TimeToLiveSystem() {

}

void TimeToLiveSystem::ProcessEntity(uint_fast64_t entity) {
	auto ttl = GetEntityComponent<TTLComponent*>(entity, TTLComponentID);

	if ((TimeRunning() - ttl->_timecreated) > ttl->_ttl) {
		GetECSManager()->RemoveEntity(entity);
	}
}
