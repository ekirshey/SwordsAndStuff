#pragma once
#include <string>
#include <unordered_map>
#include <iostream>

namespace Items {
	enum ItemSlotTypes { MAINHAND, OFFHAND, HEAD, CHEST, LEGS, FEET, HANDS, TRINKET };
	#define UNOWNED -1

	struct ItemStats {
		ItemStats() {}
		ItemStats(const ItemStats& t) : stats(t.stats) {}

		std::unordered_map<int, double> stats;
	};

	struct ItemProperties {
		ItemProperties() : material(0), quality(0) {
			
		}
		ItemProperties(const ItemProperties& t) {}
		int material;
		int quality;
	};

	struct ItemLore {
		ItemLore(std::string name, std::string description) : name(name), description(description) {
		}

		ItemLore() : name("DEFAULT"), description("NONE") {

		}

		ItemLore(const ItemLore& i) : name(i.name), description(i.description) {
			
		}

		std::string name;
		std::string description;
	};

	struct ItemTriggers {
		ItemTriggers() {}
		ItemTriggers(const ItemTriggers& t) {}
		//Triggers
	};

	class Item {
		public:
			std::string GetName() { return lore_.name; }

			friend class ItemDatabase;

			int id_;
			uint_fast64_t owner_;

		private:

			Item::Item(int id, const ItemStats& stats, const ItemProperties& properties, const ItemLore& lore, const ItemTriggers& triggers) : 
				id_(id), owner_(UNOWNED), stats_(stats),
				properties_(properties),
				lore_(lore),
				triggers_(triggers) {
			}

			ItemStats stats_;
			ItemProperties properties_;
			ItemLore lore_;
			ItemTriggers triggers_;
			
	};
}