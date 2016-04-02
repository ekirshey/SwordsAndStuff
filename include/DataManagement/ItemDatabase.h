#pragma once
#include <list>
#include <memory>
#include "../Types/Items.h"

namespace Items {

	class ItemDatabase
	{
	public:
		ItemDatabase();
		~ItemDatabase();
		Item* CreateItem(const ItemStats& stats, const ItemProperties& properties, const ItemLore& lore, const ItemTriggers& triggers);

		Item* GetItem(int id) {
			return &items_[id];
		};

		void RemoveItem(int id);
	private:
		std::vector<Item> items_;
	};

}