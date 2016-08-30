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
		BoundingRectangleComponent(int x, int y, int width, int height) : x_(x), y_(y), width_(width), height_(height) {}
		BoundingRectangleComponent(const BoundingRectangleComponent& c) : x_(c.x_), y_(c.y_), width_(c.width_), height_(c.height_) {}

		~BoundingRectangleComponent() {}

		uint_fast64_t UniqueBits() const { return ID; }

		SDL_Rect Rectangle() const { return SDL_Rect{ x_, y_, width_, height_ }; }

		int x_;
		int y_;
		int width_;
		int height_;

};


#endif // BOUNDINGRECTANGLECOMPONENT_H
