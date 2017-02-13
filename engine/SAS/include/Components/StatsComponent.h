#pragma once

#include <unordered_map>
#include "ECSFramework/Component.h"
#include "Config/ComponentDefines.h"
#include "Types/Stats.h"

class StatsComponent : public Component
{
    public:
        static const uint_fast64_t ID = StatsComponentID;

        StatsComponent(MainStatMap main, DerivedStatMap derived) : _mainstats(main), _derivedstats(derived) {}
        StatsComponent(const StatsComponent& c) : _mainstats(c._mainstats), _derivedstats(c._derivedstats) { }

        ~StatsComponent() {}

        uint_fast64_t UniqueBits() const {return ID;}

		MainStatMap _mainstats;
		DerivedStatMap _derivedstats;
};