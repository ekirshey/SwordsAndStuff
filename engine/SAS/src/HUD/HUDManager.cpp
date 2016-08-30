#include "../../include/HUD/HUDManager.h"
#include "../../include/HUD/HUDComponents/FillBar.h"
#include "../../include/ECSFramework/Component.h"
#include "../../include/Components/RPGStatsComponent.h"
#include "SDLManager.h""

#include <iostream>

HUDManager::HUDManager()
{
    //ctor
}

HUDManager::HUDManager(SAS_Rendering::SDLManager* sdlmanager) : sdlmanager_(sdlmanager)
{
	Initialize();
}

HUDManager::~HUDManager()
{
    //dtor
}

void HUDManager::Update()
{
    for (unsigned int i = 0; i < hudcomponents.size(); i++)
    {
        hudcomponents[i]->Update();
        hudcomponents[i]->Render();
    }
}

//void HUDManager::Initialize()
void HUDManager::Initialize() 
{
/*
    RPGStatsComponent* playerstats;

    std::vector<Component*> playercomponents = objectmanager_->GetAllPlayerComponents();
	if (playercomponents.empty())
		std::cout << "HUDMANAGER: No Player, exit gracefully" << std::endl;
	else
	{
		//hudcomponents.push_back(std::unique_ptr<HUDComponent>(new FillBar(trackedstat)));
		for (int i = 0; i < playercomponents.size(); i++)
		{
			if (playercomponents[i]->UniqueBits() == RPGStatsComponent::ID)
				playerstats = static_cast<RPGStatsComponent*>(playercomponents[i]);
		}

		hudcomponents.push_back(std::unique_ptr<HUDComponent>(new FillBar(playerstats->GetStatPtr(HEALTH), sdlmanager_)));
	}
*/

}
