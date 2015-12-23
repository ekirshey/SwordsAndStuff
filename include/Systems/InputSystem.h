#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include "../Systems/ProcessingSystem.h"

class SDLManager;
class InputSystem : public ProcessingSystem
{
    public:
        static const uint_fast64_t COMPONENTIDS = 0x13;     // Input Component, Angle Component, Position Component

        InputSystem(ECSManager* ECSManager, SDLManager* sdlmanager);
        ~InputSystem();

        uint_fast64_t ComponentBits() {return InputSystem::COMPONENTIDS;}    // TODO: Is this necessary or is just accessing the variable directly better?

        void ProcessEntity(uint_fast64_t entity);
    private:
        SDLManager* sdlmanager_;
        const uint8_t* keyboardstate_;
        bool* mousestate_;

};

#endif // INPUTSYSTEM_H
