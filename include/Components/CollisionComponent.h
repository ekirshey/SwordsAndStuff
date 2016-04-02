#pragma once

#include "../../include/ECSFramework/Component.h"
#include "../Config/ComponentDefines.h"

class CollisionComponent : public Component
{
public:
	static const uint_fast64_t ID = CollisionComponentID;

	CollisionComponent() {}
	CollisionComponent(int x, int y) : x_(x), y_(y) {}
	CollisionComponent(const CollisionComponent& c) : x_(c.x_), y_(c.y_) {}

	~CollisionComponent() {}

	uint_fast64_t UniqueBits() const { return ID; }

	int x_;
	int y_;

	// Future Position
};

