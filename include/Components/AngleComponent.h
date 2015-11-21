#ifndef ANGLECOMPONENT_H
#define ANGLECOMPONENT_H

#include "../../include/ECSFramework/Component.h"
#include "../Config/ComponentDefines.h"

class AngleComponent : public Component
{
    public:
        static const uint_fast64_t ID = AngleComponentID;

        AngleComponent() {}
        AngleComponent(double angle) : angle_(angle) {}
        AngleComponent(const AngleComponent& c) : angle_(c.Angle()) {}

        virtual ~AngleComponent() {}

        uint_fast64_t UniqueBits() const {return ID;}

        double Angle() const {return angle_;}

        void SetAngle(double angle) { angle_ = angle;}

    private:
        double angle_;

};


#endif // ANGLECOMPONENT_H
