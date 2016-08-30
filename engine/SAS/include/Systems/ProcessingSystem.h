#ifndef PROCESSINGSYSTEM_H
#define PROCESSINGSYSTEM_H

#include "../ECSFramework/System.h"

class ProcessingSystem : public System
{
    public:
        ProcessingSystem(std::string systemname, ECSManager* ecsmanager);
        virtual ~ProcessingSystem();

        virtual void ProcessEntity(uint_fast64_t entity) = 0;
        void ProcessEntities();

        virtual void BeforeObjectProcessing() {}
        virtual void AfterObjectProcessing() {}
};

#endif // PROCESSINGSYSTEM_H
