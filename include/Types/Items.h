#pragma once
#include <string>

enum ItemSlotTypes { MAINHAND, OFFHAND, HEAD, CHEST, LEGS, FEET, HANDS, TRINKET, INVENTORY };

struct ItemStats {
	double minattack;
	double maxattack;
	ItemStats(double minatk, double maxatk) : minattack(minatk), maxattack(maxatk) {}
};

struct Item {
	std::string name;
	int slottype;
	int itemtype;
	ItemStats stats;
	Item(std::string name, int slottype, int itemtype, ItemStats stats) :
		name(name), slottype(slottype), itemtype(itemtype), stats(stats) {

	}
};
