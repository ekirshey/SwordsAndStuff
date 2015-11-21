#ifndef TRIGGEREDSYSTEM_H
#define TRIGGEREDSYSTEM_H

#include <vector>
#include <cstdint>
#include "../ECSFramework/System.h"

class TriggeredSystem : public System
{
    public:
        TriggeredSystem(ECSManager* ECSManager);
        virtual ~TriggeredSystem();

        virtual void ProcessEntity(uint_fast64_t entity) = 0;
        void ProcessEntities();

        void AddTriggeredEntity(uint_fast64_t triggeredentity);
        void SetTriggeredEntityList(std::vector<uint_fast64_t> triggeredentities);
    private:
        std::vector<uint_fast64_t> triggeredentities_;
};

#endif // TRIGGEREDSYSTEM_H
