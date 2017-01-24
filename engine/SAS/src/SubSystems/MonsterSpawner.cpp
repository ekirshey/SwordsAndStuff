#include <iostream>
#include <SDL.h>
#include <time.h>       /* time */
#include "../../include/SubSystems/MonsterSpawner.h"
#include "../../include/ECSFramework/ECSManager.h"
#include "../../include/Components/BoundingRectangleComponent.h"
#include "../../include/Components/RenderComponent.h"
#include "../../include/Components/PositionComponent.h"
#include "../../include/Components/AngleComponent.h"
#include "../../include/Components/VelocityComponent.h"

#define STARTY -5

//TODO Actual Random numbers

MonsterSpawner::MonsterSpawner( std::string tag, int maxactivemonsters, ECSManager* ecsmanager) :
    maxactivemonsters_(maxactivemonsters), tag_(tag), ecsmanager_(ecsmanager)
{
    taggedentities_ = ecsmanager_->GetPtrToAssociatedEntities(tag);
    srand (time(NULL));
}

void MonsterSpawner::SpawnMonsters()
{
    int monsterstospawn;
    int monsterentity;
    int velocityx, velocityy;
    int startx;
    int destinationx;

    std::string path;

    if (taggedentities_ == nullptr)
        monsterstospawn = maxactivemonsters_;
    else
    {
        int difference = maxactivemonsters_ - taggedentities_->size();
        if (difference > 1 )
            monsterstospawn = rand() % (difference) + 1;
        else
            monsterstospawn = difference;
    }

    if ((rand() % 10) <= 3 )
    {
        for (int i = 0; i < monsterstospawn; i++)
        {
            SDL_Rect rect = {0,0,30,30};
            path = "sprites\\monster.png";

            velocityy = 2;//rand() % 5 + 1;

            startx = rand() % 730;
            destinationx = rand() % 730;
            velocityx = (destinationx - startx)/605;

            monsterentity = ecsmanager_->CreateEntity();
			ecsmanager_->AddComponentToEntity(monsterentity, std::unique_ptr<PositionComponent>(new PositionComponent(startx,STARTY))); // TODO MAgic numbers
            ecsmanager_->AddComponentToEntity(monsterentity, std::unique_ptr<VelocityComponent>(new VelocityComponent(velocityx,velocityy)));
            ecsmanager_->AddComponentToEntity(monsterentity, std::unique_ptr<AngleComponent>(new AngleComponent(0.0))); // In degrees
            ecsmanager_->AddComponentToEntity(monsterentity, std::unique_ptr<BoundingRectangleComponent>(new BoundingRectangleComponent(startx+5,STARTY+5,20,21)));//30,30
            ecsmanager_->AddComponentToEntity(monsterentity, std::unique_ptr<RenderComponent>(new RenderComponent(path,rect, 0.0)));
            ecsmanager_->AssignEntityTag(monsterentity, "MONSTER");
        }
    }

}
