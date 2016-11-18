#pragma once

#include <string>
#include "../../include/ECSFramework/Component.h"
#include "../Config/ComponentDefines.h"

class DescriptionComponent : public Component
{
public:
	static const uint_fast64_t ID = DescriptionComponentID;

	DescriptionComponent() : _name("") {}
	DescriptionComponent(std::string name) : _name(name) {}
	DescriptionComponent(const DescriptionComponent& c) : _name(c._name) {}

	~DescriptionComponent() {}

	uint_fast64_t UniqueBits() const { return ID; }

	std::string _name;


};
