#pragma once

#include <string>
#include <SDL.h>
#include "../../include/ECSFramework/Component.h"
#include "../Config/ComponentDefines.h"

class DescriptionComponent : public Component
{
public:
	static const uint_fast64_t ID = DescriptionComponentID;

	DescriptionComponent() : name_("") {}
	DescriptionComponent(std::string name) : name_(name) {}
	DescriptionComponent(const DescriptionComponent& c) : name_(c.name_) {}

	~DescriptionComponent() {}

	uint_fast64_t UniqueBits() const { return ID; }

	std::string name_;


};
