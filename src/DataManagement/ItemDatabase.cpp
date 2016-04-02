#include <algorithm>
#include "..\..\include\DataManagement\ItemDatabase.h"

namespace Items {

	Items::ItemDatabase::ItemDatabase()
	{
	}


	ItemDatabase::~ItemDatabase()
	{
	}

	Item* ItemDatabase::CreateItem(const ItemStats& stats, const ItemProperties& properties, const ItemLore& lore, const ItemTriggers& triggers) {

		Items::Item item(
			items_.size(),
			stats,
			properties,
			lore,
			triggers
			);

		items_.push_back(item);

		return &items_.back();
	}

	void ItemDatabase::RemoveItem(int id) {
		auto it = items_.begin();
		while (it != items_.end()) {
			if (it->id_ == id) {
				items_.erase(it);
				break;
			}
		}
	}
}