#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <memory>
#include <vector>
#include <queue>
#include <cstdint>
#include "Component.h"

#define MAXOBJECTS 100000


inline int fastlog(uint_fast64_t i)
{
	int result = 0;
	while (i >>= 1) result++;
	return result;
}

class EntityManager
{
    public:
        EntityManager();
        virtual ~EntityManager();

        uint_fast64_t GetNewEntityUUID();
        void RemoveEntity(uint_fast64_t UUID);

        bool AddComponent(uint_fast64_t UUID, std::unique_ptr<Component> componenttoadd);
        bool RemoveComponent(uint_fast64_t UUID, uint_fast64_t componentid);

		uint_fast64_t EntityCount() { return entitycount_; }

		inline Component* EntityManager::GetEntityComponent(uint_fast64_t UUID, uint_fast64_t componentid)
		{
			int convertedcomponentid = fastlog(componentid);
			if (entitylist_[UUID][convertedcomponentid] != nullptr)
				return entitylist_[UUID][convertedcomponentid].get();
			else
				return nullptr;

		}

        std::vector<Component*> GetAllEntityComponents(uint_fast64_t UUID);

        uint_fast64_t GetEntityComponentBits(uint_fast64_t UUID) {return entitycomponentbits_[UUID];}

    private:
        //SystemManager* systemmanager_;
        // The index of the vector will be the UUID of the entity
        // The component vector will have a size of 64
        // I'll know what slot to place an added component in by ddoing logbase2 of UniqueBits returned from the component
        std::vector<std::unique_ptr<Component>> entitylist_[MAXOBJECTS];    // unique_ptr due to object slicing
        uint_fast64_t entitycomponentbits_[MAXOBJECTS];                     // Keeps a running update of whcih components are in the entity
                                                                             // Used specifically for adding entities to systems
        std::queue<uint_fast64_t> availableids_;
        uint_fast64_t entitycount_;
		int entitylistsize_;
};

#endif // ENTITYMANAGER_H
