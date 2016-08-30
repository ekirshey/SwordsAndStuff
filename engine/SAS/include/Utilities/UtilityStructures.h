#pragma once

#include "../Components/PositionComponent.h"
#include "../Components/VelocityComponent.h"
#include "../Components/BoundingRectangleComponent.h"

struct QuadElement
{
	uint_fast64_t entityid;
	VelocityComponent* velocitycomponent;
	PositionComponent* positioncomponent;
	BoundingRectangleComponent* boundingrectangle;

	bool operator==(const QuadElement& rhs) const
	{
		if (entityid != rhs.entityid)
			return false;
		return true;
	}

	bool operator<(const QuadElement& p) const {
		return entityid < p.entityid;
	}
	bool operator!=(const QuadElement& p) const { return !(*this == p); }
	bool operator> (const QuadElement& p) const { return p < *this; }
	bool operator>=(const QuadElement& p) const { return !(*this < p); }
	bool operator<=(const QuadElement& p) const { return !(p < *this); }
};