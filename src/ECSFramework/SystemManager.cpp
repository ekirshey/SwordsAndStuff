#include <iostream>
#include "../../include/ECSFramework/ECSManager.h"
#include "../../include/ECSFramework/SystemManager.h"
#include "../../include/ECSFramework/System.h"

static const int SYSTEM_LIST_STEP_SIZE = 100;

SystemManager::SystemManager()
{
    systemcount_ = 0;
    systemlist_.resize(SYSTEM_LIST_STEP_SIZE);

    for (unsigned int i = 0; i < systemlist_.size(); i++)
        systemlist_[i] = std::unique_ptr<System>();
}

SystemManager::~SystemManager()
{
    //dtor
}

int SystemManager::AddSystem(std::unique_ptr<System> system, int priority)
{
	int systemindex = -1;

    // TODO: Resize and shift priorities
    if ( systemlist_[priority].get() == nullptr)
    {
        systemlist_[priority] = std::move(system);
		systemindex = priority;	// EKTEMP fetching by priority this isnt bad actually because -1 means failed to add
        systemcount_++;
    }
    else
        std::cout << "System with priority " << priority << " exists" << std::endl;

	return systemindex;
}

System* SystemManager::GetSystem(int priority)
{
	System* system = nullptr;
	if (priority >= 0 && priority < systemlist_.size())
		system = systemlist_[priority].get();

	return system;
}

void SystemManager::RemoveSystem(int systemid, int priority)
{
    // TODO No rush, how often are you going to remove a system? I cant even imagine why
}

void SystemManager::AddEntityToSystem(uint_fast64_t entity, uint_fast64_t entitycomponents)
{
    for (unsigned int i = 0; i < systemcount_; i++)
    {
        if ( systemlist_[i]->ValidEntity(entitycomponents,systemlist_[i]->ComponentBits()))
            systemlist_[i]->AddEntity(entity);
    }
}

// TODO Test
void SystemManager::RemoveEntityFromSystems(uint_fast64_t entity, uint_fast64_t entitycomponents)
{
    for (unsigned int i = 0; i < systemcount_; i++)
    {
        if ( systemlist_[i]->ContainsEntity(entity) && !systemlist_[i]->ValidEntity(entitycomponents,systemlist_[i]->ComponentBits()))
            systemlist_[i]->RemoveEntity(entity);
    }
}

void SystemManager::RemoveEntityFromSystems(uint_fast64_t entity)
{
    for (unsigned int i = 0; i < systemcount_; i++)
        systemlist_[i]->RemoveEntity(entity);
}

void SystemManager::Update(int elapsedtime)
{
    for (unsigned int i = 0; i < systemcount_; i++)
    {
        systemlist_[i]->Update(elapsedtime);
    }
}
