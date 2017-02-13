#ifndef POSITIONCOMPONENT_H
#define POSITIONCOMPONENT_H

#include "../../include/ECSFramework/Component.h"
#include "../Config/ComponentDefines.h"
#include <iostream>

enum Facing {NORTH = 0, EAST, SOUTH, WEST};

class PositionComponent : public Component
{
    public:
        static const uint_fast64_t ID = PositionComponentID;

        PositionComponent() {}
		PositionComponent(int x, int y) : x_(x), y_(y), facing_(NORTH) {}
        PositionComponent(int x, int y, int facing) : x_(x), y_(y), facing_(facing) {}
        PositionComponent(const PositionComponent& c) : x_(c.x_), y_(c.y_), facing_(c.facing_) {

		}

        ~PositionComponent() {}

        uint_fast64_t UniqueBits() const {return ID;}

        int x_;
        int y_;
		int facing_;

};

#endif // POSITIONCOMPONENT_H
