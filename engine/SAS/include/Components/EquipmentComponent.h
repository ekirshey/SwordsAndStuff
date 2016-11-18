#pragma once
#include <cstdint>
#include <vector>
#include "ECSFramework/Component.h"
#include "Config/ComponentDefines.h"
#include "Types/Items.h"

struct EquipmentSlot {
	Items::Item* item;
	EquipmentSlot(Items::Item* item) : item(item) {}
};

class EquipmentComponent : public Component
{
public:
	static const uint_fast64_t ID = EquipmentComponentID;

	EquipmentComponent() { 
		for (int i = Items::MAINHAND; i <= Items::TRINKET; i++)
			equipment_.push_back(EquipmentSlot(nullptr));
	}

	~EquipmentComponent() {}

	uint_fast64_t UniqueBits() const { return ID; }

	std::vector<EquipmentSlot> equipment_;

};