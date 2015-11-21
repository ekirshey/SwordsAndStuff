#define _USE_MATH_DEFINES

#include <iostream>
#include <SDL.h>
#include <math.h>
#include "../../include/ECSFramework/ECSManager.h"
#include "../../include/Systems/ShootingSystem.h"
#include "../../include/Components/PositionComponent.h"
#include "../../include/Components/VelocityComponent.h"
#include "../../include/Components/ShootingComponent.h"
#include "../../include/Components/RenderComponent.h"
#include "../../include/Components/AngleComponent.h"
#include "../../include/Components/BoundingRectangleComponent.h"

#include "../../include/Components/RPGStatsComponent.h"

ShootingSystem::ShootingSystem(ECSManager* ECSManager) : ProcessingSystem(ECSManager)
{

}

ShootingSystem::~ShootingSystem()
{
    //dtor
}

void ShootingSystem::ProcessEntity(uint_fast64_t entity)
{
    int currenttime;
    int anglesign = 1;

    // Components to use
    //PositionComponent* positioncomponent;
    AngleComponent* anglecomponent;
    ShootingComponent* shootingcomponent;
    BoundingRectangleComponent* boundingrectanglecomponent;
    RPGStatsComponent* stats;

    // Get Relevant Component Data
    //positioncomponent = static_cast<PositionComponent*>(GetECSManager()->GetEntityComponent(entity,PositionComponent::ID));
    anglecomponent = static_cast<AngleComponent*>(GetECSManager()->GetEntityComponent(entity,AngleComponent::ID));
    shootingcomponent = static_cast<ShootingComponent*>(GetECSManager()->GetEntityComponent(entity,ShootingComponent::ID));
    boundingrectanglecomponent = static_cast<BoundingRectangleComponent*>(GetECSManager()->GetEntityComponent(entity,BoundingRectangleComponent::ID));
    stats = static_cast<RPGStatsComponent*>(GetECSManager()->GetEntityComponent(entity,RPGStatsComponent::ID));

    if (shootingcomponent->ShotsFired())
    {
        currenttime = SDL_GetTicks();
        shootingcomponent->Shoot(false);
        stats->SetStat(HEALTH, stats->GetStat(HEALTH)-1);

        if ( (currenttime - shootingcomponent->TimeOfLastShot()) >= shootingcomponent->Cooldown() )
        {
            shootingcomponent->SetTimeOfLastShot(currenttime);

            // Create New Bullet
            double angle = anglecomponent->Angle() * (M_PI/180); // In radians
            if ( angle > 0)
                anglesign = (angle/angle);
            int bullet = GetECSManager()->CreateEntity();
            SDL_Rect rect = {0,0,2,6}; // Removed top pixel due to a black line showing up when rotating

            std::string path = "media\\sprites\\bullet.png";
            GetECSManager()->AddComponentToEntity(bullet, new PositionComponent( (boundingrectanglecomponent->X() + boundingrectanglecomponent->Width()/2),
                                                                                 (boundingrectanglecomponent->Y()+5))); // TODO MAgic numbers
            GetECSManager()->AddComponentToEntity(bullet, new AngleComponent(anglecomponent->Angle())); // In degrees
            GetECSManager()->AddComponentToEntity(bullet, new BoundingRectangleComponent((boundingrectanglecomponent->X() + boundingrectanglecomponent->Width()/2),
                                                                                         (boundingrectanglecomponent->Y()),2,6));
            GetECSManager()->AddComponentToEntity(bullet, new VelocityComponent(anglesign * 5 * sin(angle),-5 * cos(angle)));
            GetECSManager()->AddComponentToEntity(bullet, new RenderComponent(path,rect));
            GetECSManager()->AssignEntityTag(bullet, "BULLET");

        }

    }

}

