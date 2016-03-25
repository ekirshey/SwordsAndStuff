#pragma once
#include <string>

enum ItemSlotTypes { MAINHAND, OFFHAND, HEAD, CHEST, LEGS, FEET, HANDS, TRINKET };

struct Item {
	std::string name;
	std::string description;
	Item(std::string name, std::string description) :
		name(name), description(description) {

	}
};
