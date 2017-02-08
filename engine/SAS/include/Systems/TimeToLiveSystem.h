#pragma once

#include "Systems/ProcessingSystem.h"
#include "Config/ComponentDefines.h"

class TimeToLiveSystem : public ProcessingSystem
{
    public:
        static const uint_fast64_t COMPONENTIDS = TTLComponentID; 

        TimeToLiveSystem(std::string systemname, ECSManager* ecsmanager);
        ~TimeToLiveSystem();

        uint_fast64_t ComponentBits() {return TimeToLiveSystem::COMPONENTIDS;}

        void ProcessEntity(uint_fast64_t entity);
};