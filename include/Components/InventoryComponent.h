#ifndef INVENTORYCOMPONENT_H
#define INVENTORYCOMPONENT_H

#include <cstdint>
#include <vector>
#include "../../include/ECSFramework/Component.h"
#include "../Config/ComponentDefines.h"

class InventoryComponent : public Component
{
    public:
        static const uint_fast64_t ID = InventoryComponentID;

        InventoryComponent() {}
        InventoryComponent(int maxinventorysize) : maxinventorysize_(maxinventorysize) {}
        InventoryComponent(const InventoryComponent& c) : maxinventorysize_(c.MaxInventorySize()){}

        virtual ~InventoryComponent() {}

        uint_fast64_t UniqueBits() const {return ID;}

        std::vector<uint_fast64_t> Inventory() const{return inventory_;}
        int MaxInventorySize() const { return maxinventorysize_;}

        void AddInventoryItem(uint_fast64_t item) {inventory_.push_back(item);}
        //void RemoveInventoryItem(uint_fast64_t item) {inventory}

    private:
        std::vector<uint_fast64_t> inventory_;
        int maxinventorysize_;
};

#endif // INVENTORYCOMPONENT_H
