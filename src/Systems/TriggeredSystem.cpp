#include "../../include/ECSFramework/ECSManager.h"
#include "../../include/Systems/TriggeredSystem.h"

TriggeredSystem::TriggeredSystem(ECSManager* ECSManager) : System(ECSManager)
{
    //ctor
    triggeredentities_.clear();
}

TriggeredSystem::~TriggeredSystem()
{
    //dtor
}

void TriggeredSystem::AddTriggeredEntity(uint_fast64_t triggeredentity)
{
    if (ValidEntity(triggeredentity,ComponentBits()))
        triggeredentities_.push_back(triggeredentity);
}

void TriggeredSystem::SetTriggeredEntityList(std::vector<uint_fast64_t> triggeredentities)
{
    triggeredentities_.clear();
    for (unsigned int i = 0; i < triggeredentities.size(); i++)
        AddTriggeredEntity(triggeredentities[i]);
}


void TriggeredSystem::ProcessEntities()
{
    for (unsigned int i = 0; i < triggeredentities_.size(); i++)
    {
        ProcessEntity(triggeredentities_[i]);
    }
}
