#ifndef VELOCITYCOMPONENT_H
#define VELOCITYCOMPONENT_H

#include "../ECSFramework/Component.h"
#include "../Config/ComponentDefines.h"

class VelocityComponent : public Component
{
    public:
        static const uint_fast64_t ID = VelocityComponentID;

        VelocityComponent() {}
        VelocityComponent(int xvelocity, int yvelocity) : xvelocity_(xvelocity), yvelocity_(yvelocity) {}
        VelocityComponent(const VelocityComponent& c) : xvelocity_(c.XVelocity()), yvelocity_(c.YVelocity()) {}

        virtual ~VelocityComponent() {}

        uint_fast64_t UniqueBits() const {return ID;}

		int XVelocity() const {return xvelocity_;}
		int YVelocity() const {return yvelocity_;}

        void SetXVelocity(int xvelocity) { xvelocity_ = xvelocity;}
        void SetYVelocity(int yvelocity) { yvelocity_ = yvelocity;}
    private:
		int xvelocity_;
		int yvelocity_;
};

#endif // VELOCITYCOMPONENT_H
