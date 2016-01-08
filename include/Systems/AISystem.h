#pragma once
#include "../Systems/ProcessingSystem.h"
#include "../Config/ComponentDefines.h"

class AIScripted;
class AIPathing;

class AISystem : public ProcessingSystem
{
	public:
		static const uint_fast64_t COMPONENTIDS = AIComponentID;
		AISystem();
		~AISystem();

		uint_fast64_t ComponentBits() { return AISystem::COMPONENTIDS; }    // TODO: Is this necessary or is just accessing the variable directly better?

		void ProcessEntity(uint_fast64_t entity);
	private:

};

