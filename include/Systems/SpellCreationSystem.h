#ifndef SPELLCREATIONSYSTEM_H
#define SPELLCREATIONSYSTEM_H

#include "../Systems/QueueSystem.h"
#include "../Config/ComponentDefines.h"


class SpellCreationSystem : public QueueSystem
{
	public:
		static const uint_fast64_t COMPONENTIDS = PositionComponentID;
		// Unlike the component ID this can be duplicated
		SpellCreationSystem(MessageQueue* messagequeue);
		~SpellCreationSystem();

		uint_fast64_t ComponentBits() { return SpellCreationSystem::COMPONENTIDS; }    // TODO: Is this necessary or is just accessing the variable directly better?

		void ProcessMessage(Message* data);

	private:

};

#endif // SPELLCREATIONSYSTEM_H
