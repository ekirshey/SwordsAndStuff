#ifndef SHOOTINGCOMPONENT_H
#define SHOOTINGCOMPONENT_H

#include "../../include/ECSFramework/Component.h"
#include "../Config/ComponentDefines.h"

class ShootingComponent : public Component
{
    public:
        static const uint_fast64_t ID = ShootingComponentID;

        ShootingComponent() {}
        ShootingComponent(int cooldown) : cooldown_(cooldown) {shotsfired_ = false; timeoflastshot_= 0;}
        ShootingComponent(const ShootingComponent& c) : cooldown_(c.Cooldown())  {shotsfired_ = false; timeoflastshot_= 0;}

        virtual ~ShootingComponent() {}

        uint_fast64_t UniqueBits() const {return ID;}

        void Shoot(bool shotsfired) {shotsfired_ = shotsfired;}
        void SetCooldown(int cooldown) {cooldown_ = cooldown;}
        void SetTimeOfLastShot(int time) { timeoflastshot_ = time;}

        bool ShotsFired() const {return shotsfired_;}
        int Cooldown() const {return cooldown_;}
        int TimeOfLastShot() const {return timeoflastshot_;}

    private:
        bool shotsfired_;       // Tells the Shooting system to create a bullet
        int cooldown_;          // Time before you can shoot again in milliseconds
        int timeoflastshot_;    // In ms sicne thats what GetTicks returns


};

#endif // SHOOTINGCOMPONENT_H
