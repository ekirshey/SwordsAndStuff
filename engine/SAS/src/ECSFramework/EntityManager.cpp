#include <cmath>
#include <iostream> //Debugging
#include "../../include/ECSFramework/EntityManager.h"
#include <chrono>

static const int ENTITY_LIST_STEP_SIZE = 500;
static const int MAX_COMPONENT_LIST = 64;

EntityManager::EntityManager() : entitylistsize_(MAXOBJECTS)
{
    entitycount_ = 0;

    //entitylist_.resize(ENTITY_LIST_STEP_SIZE);
    //entitycomponentbits_.resize(ENTITY_LIST_STEP_SIZE);

    for( unsigned int i = 0; i < entitylistsize_; i++)
    {
        entitylist_[i] = std::vector<std::unique_ptr<Component>>();
        entitylist_[i].resize(MAX_COMPONENT_LIST);
        entitycomponentbits_[i] = 0;
    }

}

EntityManager::~EntityManager()
{
    //dtor
}

uint_fast64_t EntityManager::GetNewEntityUUID()
{
    uint_fast64_t entityid = 0;

    if (!availableids_.empty())
   { 
        entityid = *availableids_.begin();
        availableids_.erase(availableids_.begin());

        // Reset the component vector TODO probably not an issue now but idk if this is slow
        entitylist_[entityid] = std::vector<std::unique_ptr<Component>>();
        entitylist_[entityid].resize(MAX_COMPONENT_LIST);
    }
    else
        entityid = entitycount_++;

    return entityid;
}

void EntityManager::RemoveEntity(uint_fast64_t UUID)
{
	// EKTEMP I think if you are moving new unique_ptr's into it then you dont need to clear
    //entitylist_[UUID].clear();
    entitycomponentbits_[UUID] = 0;

    availableids_.insert(UUID);
}

// If a component is ADDED to an entity then the SystemManager needs to be made aware
// so it can ADD the entity to the appropriate system if it NOW meets the conditions
bool EntityManager::AddComponent(uint_fast64_t UUID, std::unique_ptr<Component> componenttoadd)
{
    int componentid;
    bool returnvalue = false;

    // Make sure if the entity is within the vector bounds and that it is an actual entity
    if ( ( UUID < MAXOBJECTS) && (entitylist_[UUID].size() > 0) )
    {
        if ( !(entitycomponentbits_[UUID] & componenttoadd->UniqueBits()) )
        {
			componentid = fastlog(componenttoadd->UniqueBits());
			entitycomponentbits_[UUID] |= componenttoadd->UniqueBits();

			// I'm moving the pointer so either eaccess the entitylist or do this last if you need the ID bits
			entitylist_[UUID].at(componentid) = std::move(componenttoadd);

			returnvalue = true;
        }
        else
            std::cout << "Duplicate Component ID " << componenttoadd->UniqueBits() << std::endl;
    }
    else
        std::cout << "Adding Component " << componenttoadd->UniqueBits() << " to UUID " << UUID << " failed, Entity does not exist! " << entitylistsize_ << std::endl;

    return returnvalue;
}

// If a component is REMOVED from an entity then the SystemManager needs to be made aware
// so it can REMOVE the entity to the appropriate system if it NO LONGER meets the conditions
bool EntityManager::RemoveComponent(uint_fast64_t UUID, uint_fast64_t componentid)
{
    // Remove component from an entity
    entitylist_[UUID].at(fastlog(componentid)) = nullptr;
    entitycomponentbits_[UUID] &= (componentid ^ 0xFFFFFFFFFFFFFFFF);

    return true;
}

std::vector<Component*> EntityManager::GetAllEntityComponents(uint_fast64_t UUID)
{
    std::vector<Component*> components;

    for (unsigned int i = 0; i < entitylist_[UUID].size(); i++)
    {
        if (entitylist_[UUID][i] != nullptr)
            components.push_back(entitylist_[UUID].at(i).get());
    }

    return components;
}
