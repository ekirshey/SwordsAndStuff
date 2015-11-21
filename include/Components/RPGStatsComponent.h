#ifndef RPGSTATSCOMPONENT_H
#define RPGSTATSCOMPONENT_H

#include "../../include/ECSFramework/Component.h"
#include "../Config/ComponentDefines.h"

#define HEALTHCONSTANTS 10.0f
#define MANACONSTANTS 10.0f

enum Stats {STRENGTH = 0, INTELLIGENCE, HEALTH, MANA};
#define TOTALSTATS 4
class RPGStatsComponent : public Component
{
    public:
        static const uint_fast64_t ID = RPGStatsComponentID;

        RPGStatsComponent()
        {
			stats_.resize(TOTALSTATS);
            stats_[STRENGTH] = 10.0f;
			stats_[INTELLIGENCE] = 10.0f;
            DerivedStats();
        }

		RPGStatsComponent(float strength, float intelligence)
        {
			stats_.resize(TOTALSTATS);
			stats_[STRENGTH] = strength;
			stats_[INTELLIGENCE] = intelligence;
            DerivedStats();
        }

        RPGStatsComponent(const RPGStatsComponent& c)
        {
			stats_[STRENGTH] = c.GetStat(STRENGTH);
			stats_[INTELLIGENCE] = c.GetStat(INTELLIGENCE);
            DerivedStats();
        }

        virtual ~RPGStatsComponent() {}

        uint_fast64_t UniqueBits() const {return ID;}

		float GetStat(int statid) const { return stats_[statid]; }
        float* GetStatPtr(int statid) { return &stats_[statid];}

		void SetStat(int statid, float value) { stats_[statid] = value; }

    private:
        void DerivedStats()
        {
            // Calculate derived stats
           stats_[HEALTH] = stats_[STRENGTH] * HEALTHCONSTANTS;
		   stats_[MANA] = stats_[INTELLIGENCE] * MANACONSTANTS;
        }

		std::vector<float> stats_;
};

#endif // RPGSTATSCOMPONENT_H
