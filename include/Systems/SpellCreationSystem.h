#ifndef SPELLCREATIONSYSTEM_H
#define SPELLCREATIONSYSTEM_H

#include "../Systems/ProcessingSystem.h"
#include "../Config/ComponentDefines.h"


class SpellCreationSystem : public ProcessingSystem
{
	public:
		static const uint_fast64_t COMPONENTIDS = PositionComponentID;
		// Unlike the component ID this can be duplicated
		SpellCreationSystem(ECSManager* ECSManager);
		virtual ~SpellCreationSystem();

		uint_fast64_t ComponentBits() { return SpellCreationSystem::COMPONENTIDS; }    // TODO: Is this necessary or is just accessing the variable directly better?

		void ProcessEntity(uint_fast64_t entity);

	private:

};

#endif // SPELLCREATIONSYSTEM_H
