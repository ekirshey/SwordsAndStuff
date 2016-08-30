#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include "../Systems/ProcessingSystem.h"

namespace SAS_Rendering {
	class SDLManager;
}
class InputSystem : public ProcessingSystem
{
	public:
		static const uint_fast64_t COMPONENTIDS = 0x13;     // Input Component, Angle Component, Position Component

		InputSystem(std::string systemname, ECSManager* ecsmanager, SAS_Rendering::SDLManager* sdlmanager);
		~InputSystem();

		uint_fast64_t ComponentBits() {return InputSystem::COMPONENTIDS;}    // TODO: Is this necessary or is just accessing the variable directly better?

		void ProcessEntity(uint_fast64_t entity);
	private:
		SAS_Rendering::SDLManager* sdlmanager_;

};

#endif // INPUTSYSTEM_H
