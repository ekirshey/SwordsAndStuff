#ifndef SPELLCREATIONSYSTEM_H
#define SPELLCREATIONSYSTEM_H

#include "../Systems/QueueSystem.h"
#include "../Config/ComponentDefines.h"

/* Since QueueSystems handle messages they dont need to 
   set componentids. I might want to think of a nicer
   interface for that.
*/
class SpellCreationSystem : public QueueSystem
{
	public:
		// Unlike the component ID this can be duplicated
		SpellCreationSystem(MessageQueue* messagequeue);
		~SpellCreationSystem();

		void AfterObjectProcessing();

		void ProcessMessage(Message* data);

	private:
		std::vector<uint_fast64_t> castspells_;

};

#endif // SPELLCREATIONSYSTEM_H
