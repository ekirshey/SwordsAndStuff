#pragma once
#include "ProcessingSystem.h"
#include "../Config/ComponentDefines.h"

class WaypointSystem : public ProcessingSystem
{
	public:
		static const uint_fast64_t COMPONENTIDS = ScriptComponentID;
		WaypointSystem(std::string systemname, ECSManager* ecsmanager);
		~WaypointSystem();
		uint_fast64_t ComponentBits() { return WaypointSystem::COMPONENTIDS; }

		void ProcessEntity(uint_fast64_t entity);
	private:
};