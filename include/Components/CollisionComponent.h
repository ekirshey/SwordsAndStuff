#pragma once

#include "../../include/ECSFramework/Component.h"
#include "../Config/ComponentDefines.h"

class CollisionComponent : public Component
{
public:
	static const uint_fast64_t ID = CollisionComponentID;

	CollisionComponent() {}
	CollisionComponent(int x, int y) : x_(x), y_(y) {}
	CollisionComponent(const CollisionComponent& c) : x_(c.X()), y_(c.Y()) {}

	~CollisionComponent() {}

	uint_fast64_t UniqueBits() const { return ID; }

	int X() const { return x_; }
	int Y() const { return y_; }

	void SetX(int x) { x_ = x; }
	void SetY(int y) { y_ = y; }

private:
	int x_;
	int y_;

	// Future Position
};

