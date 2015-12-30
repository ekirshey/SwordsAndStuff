#include "../../include/ECSFramework/ECSManager.h"
#include "../../include/Systems/ProcessingSystem.h"
#include <iostream>
ProcessingSystem::ProcessingSystem() 
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
	//std::cout << SystemName() << " " << entities.size() << std::endl;
    for (unsigned int i = 0; i < entities.size(); i++)
    {
        ProcessEntity(entities[i]);
    }

    AfterObjectProcessing();
}
