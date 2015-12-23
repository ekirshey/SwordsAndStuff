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
		BoundingRectangleComponent(const BoundingRectangleComponent& c) : x_(c.X()), y_(c.Y()), width_(c.Width()), height_(c.Height()) {}

		~BoundingRectangleComponent() {}

		uint_fast64_t UniqueBits() const { return ID; }

		int X() const { return x_; }
		int Y() const { return y_; }
		int Width() const { return width_; }
		int Height() const { return height_; }

		void SetX(int x) { x_ = x; }
		void SetY(int y) { y_ = y; }
		void SetWidth(int width) { width_ = width; }
		void SetHeight(int height) { height_ = height; }

		SDL_Rect Rectangle() const { return SDL_Rect{ x_, y_, width_, height_ }; }

	private:
		int x_;
		int y_;
		int width_;
		int height_;

};


#endif // BOUNDINGRECTANGLECOMPONENT_H
