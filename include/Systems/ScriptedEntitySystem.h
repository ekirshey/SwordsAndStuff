#pragma once
#include "ProcessingSystem.h"
#include "../Config/ComponentDefines.h"

class ScriptedEntitySystem : public ProcessingSystem
{
	public:
		static const uint_fast64_t COMPONENTIDS = ScriptComponentID;
		ScriptedEntitySystem();
		~ScriptedEntitySystem();
		uint_fast64_t ComponentBits() { return ScriptedEntitySystem::COMPONENTIDS; }

		void ProcessEntity(uint_fast64_t entity);
	private:
};