#pragma once
#include <cstdint>
#include <vector>
#include "../../include/ECSFramework/Component.h"
#include "../Config/ComponentDefines.h"
#include "../Types/Items.h"

struct EquipmentSlot {
	int archtype;
	std::unique_ptr<Item> item;
	EquipmentSlot(int archtype, std::unique_ptr<Item> item) : archtype(archtype), item(std::move(item)) {}
};

class EquipmentComponent : public Component
{
public:
	static const uint_fast64_t ID = EquipmentComponentID;

	EquipmentComponent() { 
		for (int i = MAINHAND; i <= TRINKET; i++)
			equipment_.push_back(EquipmentSlot(i, nullptr));
	}

	// Figure out weirdness if you use unique_ptrs
	//EquipmentComponent(const EquipmentComponent& e) : equipment_(e.equipment_) {}

	~EquipmentComponent() {}

	uint_fast64_t UniqueBits() const { return ID; }

	int GetSlotType(int slot) { return equipment_[slot].archtype;  }

	void AddEquipment(std::unique_ptr<Item> item) { equipment_[item->slottype].item = std::move(item); }

	Item* GetEquipment(int slot) { return equipment_[slot].item.get(); }

private:
	std::vector<EquipmentSlot> equipment_;

};