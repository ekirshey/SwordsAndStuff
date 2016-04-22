#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include <vector>
#include <memory>
#include <cstdint>

// Forward Declarations
class System;
class ECSManager;

class SystemManager
{
    public:
		SystemManager();
        virtual ~SystemManager();

        int AddSystem(std::unique_ptr<System> system, int priority);
		System* GetSystem(int priority);
        void RemoveSystem(int systemid, int priority);

        void AddEntityToSystem(uint_fast64_t entity, uint_fast64_t entitycomponents);

        void RemoveEntityFromSystems(uint_fast64_t entity);
        void RemoveEntityFromSystems(uint_fast64_t entity, uint_fast64_t entitycomponents);

        void Update(int elapsedtime);
    private:
        std::vector<std::unique_ptr<System>> systemlist_;
        uint_fast64_t systemcount_;

};

#endif // SYSTEMMANAGER_H
