#ifndef POSITIONCOMPONENT_H
#define POSITIONCOMPONENT_H

#include "../../include/ECSFramework/Component.h"
#include "../Config/ComponentDefines.h"

class PositionComponent : public Component
{
    public:
        static const uint_fast64_t ID = PositionComponentID;

        PositionComponent() {}
        PositionComponent(int x, int y) : x_(x), y_(y) {}
        PositionComponent(const PositionComponent& c) : x_(c.X()), y_(c.Y()) {}

        ~PositionComponent() {}

        uint_fast64_t UniqueBits() const {return ID;}

        int X() const {return x_;}
        int Y() const {return y_;}

        void SetX(int x) { x_ = x;}
        void SetY(int y) { y_ = y;}

    private:
        int x_;
        int y_;

};

#endif // POSITIONCOMPONENT_H
