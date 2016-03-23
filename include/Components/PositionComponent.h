#ifndef POSITIONCOMPONENT_H
#define POSITIONCOMPONENT_H

#include "../../include/ECSFramework/Component.h"
#include "../Config/ComponentDefines.h"
#include <iostream>

enum Facing {SOUTH = 0, WEST, EAST, NORTH};

class PositionComponent : public Component
{
    public:
        static const uint_fast64_t ID = PositionComponentID;

        PositionComponent() {}
		PositionComponent(int x, int y) : x_(x), y_(y), facing_(SOUTH) {}
        PositionComponent(int x, int y, int facing) : x_(x), y_(y), facing_(facing) {}
        PositionComponent(const PositionComponent& c) : x_(c.X()), y_(c.Y()), facing_(c.Facing()) {

		}

        ~PositionComponent() {}

        uint_fast64_t UniqueBits() const {return ID;}

        int X() const {return x_;}
        int Y() const {return y_;}
		int Facing() const { return facing_; }

        void SetX(int x) { x_ = x;}
        void SetY(int y) { y_ = y;}
		void SetFacing(int facing) { facing_ = facing; }

    private:
        int x_;
        int y_;
		int facing_;

};

#endif // POSITIONCOMPONENT_H
