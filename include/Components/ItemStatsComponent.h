#ifndef ITEMSTATSCOMPONENT_H
#define ITEMSTATSCOMPONENT_H

#include "../../include/ECSFramework/Component.h"
#include "../Config/ComponentDefines.h"

class ItemStatsComponent : public Component
{
    public:
        static const uint_fast64_t ID = ItemStatsComponentID; // Subject to change. These are item specific components so I feel like it should pull from a different id set

        ItemStatsComponent() {}
        //ItemStatsComponent(int x, int y, int width, int height) : x_(x), y_(y), width_(width), height_(height) {}
        //ItemStatsComponent(const ItemStatsComponent& c) : x_(c.X()), y_(c.Y()), width_(c.Width()), height_(c.Height()) {}

        ~ItemStatsComponent() {}

        uint_fast64_t UniqueBits() const {return ID;}


    private:
        // Basic stats that all items should have. I'll consider how I want to expand on this.
        int maxdurability_;
        int currentdurability_;
        int weight_;
};

#endif // ITEMSTATSCOMPONENT_H
