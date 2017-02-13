#ifndef INVENTORYCOMPONENT_H
#define INVENTORYCOMPONENT_H

#include <cstdint>
#include <vector>
#include "ECSFramework/Component.h"
#include "Config/ComponentDefines.h"
#include "Types/Items.h"

struct InventoryComponent : public Component
{
        static const uint_fast64_t ID = InventoryComponentID;

        InventoryComponent() {}
        InventoryComponent(int maxinventorysize) : maxinventorysize_(maxinventorysize) {}
        InventoryComponent(const InventoryComponent& c) : maxinventorysize_(c.maxinventorysize_){}

        ~InventoryComponent() {}

        uint_fast64_t UniqueBits() const {return ID;}

        std::vector<Items::Item*> inventory_;
        int maxinventorysize_;
};

#endif // INVENTORYCOMPONENT_H
