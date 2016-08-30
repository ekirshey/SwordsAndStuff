#pragma once

#include "../../include/ECSFramework/Component.h"
#include "../Config/ComponentDefines.h"
#include "../Types/AITypes/AITemplate.h"

class AIComponent : public Component
{
public:
	static const uint_fast64_t ID = AIComponentID;

	AIComponent() {}
	AIComponent(AITemplate* ai) : ai_(ai) {}
	AIComponent(const AIComponent& c) : ai_(c.ai_) {}

	~AIComponent() {}

	uint_fast64_t UniqueBits() const { return ID; }

	AITemplate* ai_;

};