#pragma once

#include "ECSFramework/Component.h"
#include "Config/ComponentDefines.h"

class PositionComponent : public Component
{
    public:
        static const uint_fast64_t ID = PositionComponentID;

        PositionComponent() {}
		PositionComponent(int x, int y) : _x(x), _y(y), _angle(0.0){}
        PositionComponent(int x, int y, double angle) : _x(x), _y(y), _angle(angle) {}
        PositionComponent(const PositionComponent& c) : _x(c._x), _y(c._y), _angle(c._angle) {

		}

        ~PositionComponent() {}

        uint_fast64_t UniqueBits() const {return ID;}

        int _x;
        int _y;
		double _angle;

};