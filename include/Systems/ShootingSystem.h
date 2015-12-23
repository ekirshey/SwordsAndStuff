#ifndef SHOOTINGSYSTEM_H
#define SHOOTINGSYSTEM_H


#include "../Systems/ProcessingSystem.h"

// TODO: Have movementsystem implement a class that overwrites add and remove. when an object is added it will check if it is on screen and add it to a separate vector
// ACTUALLY no, movement needs to move every single object, this is relevant for draw type systems, render etc
class ShootingSystem : public ProcessingSystem
{
    public:
        static const uint_fast64_t COMPONENTIDS = 0x40;      // TODO adjust this appropriately
        ShootingSystem(ECSManager* ECSManager);
        ~ShootingSystem();

        uint_fast64_t ComponentBits() {return ShootingSystem::COMPONENTIDS;}    // TODO: Is this necessary or is just accessing the variable directly better?

        void ProcessEntity(uint_fast64_t entity);
};


#endif // SHOOTINGSYSTEM_H
