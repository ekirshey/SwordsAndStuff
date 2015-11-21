#include "../../include/ECSFramework/ECSManager.h"
#include "../../include/Systems/ProcessingSystem.h"

ProcessingSystem::ProcessingSystem(ECSManager* ECSManager) : System(ECSManager)
{
    //ctor
}

ProcessingSystem::~ProcessingSystem()
{
    //dtor
}

void ProcessingSystem::ProcessEntities()
{
    std::vector<uint_fast64_t> entities = RelevantEntities();

    BeforeObjectProcessing();

    for (unsigned int i = 0; i < entities.size(); i++)
    {
        ProcessEntity(entities[i]);
    }

    AfterObjectProcessing();
}
