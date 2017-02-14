#ifndef BOUNDINGRECTANGLECOMPONENT_H
#define BOUNDINGRECTANGLECOMPONENT_H

#include "../../include/ECSFramework/Component.h"
#include "../Config/ComponentDefines.h"
#include "SDL_rect.h"

class BoundingRectangleComponent : public Component
{
    public:
        static const uint_fast64_t ID = BoundingRectangleComponentID;

		BoundingRectangleComponent() {}
		BoundingRectangleComponent(int x, int y, int width, int height) : _x(x), _y(y), width_(width), height_(height) {}
		BoundingRectangleComponent(const BoundingRectangleComponent& c) : _x(c._x), _y(c._y), width_(c.width_), height_(c.height_) {}

		~BoundingRectangleComponent() {}

		uint_fast64_t UniqueBits() const { return ID; }

		SDL_Rect Rectangle() const { return SDL_Rect{ _x, _y, width_, height_ }; }

		int _x;
		int _y;
		int width_;
		int height_;

};


#endif // BOUNDINGRECTANGLECOMPONENT_H
