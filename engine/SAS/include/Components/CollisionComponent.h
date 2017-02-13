#pragma once

#include "ECSFramework/Component.h"
#include "Config/ComponentDefines.h"
#include "CollisionResolver.h"

#define NOSPAWNER -1
class CollisionComponent : public Component
{
public:
	static const uint_fast64_t ID = CollisionComponentID;

	CollisionComponent(CollisionClass c) : collidableclass(c), spawner(NOSPAWNER) {}
	CollisionComponent(CollisionClass c, uint_fast64_t spawner) : collidableclass(c), spawner(spawner) {}
	CollisionComponent(const CollisionComponent& c) : collidableclass(c.collidableclass), spawner(c.spawner){}

	~CollisionComponent() {}

	uint_fast64_t UniqueBits() const { return ID; }

	CollisionClass collidableclass;	// Enum that tells the CollisionResolver how to handle the collision, i.e. spell "dies" on collision
	uint_fast64_t spawner;	// -1 if N/A

};

