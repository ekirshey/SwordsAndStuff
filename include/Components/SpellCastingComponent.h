#pragma once

#include <string>
#include "../../include/ECSFramework/Component.h"
#include "../Config/ComponentDefines.h"

// NOTE: Determine actual spell format
class SpellCastingComponent : public Component
{
	public:
		static const uint_fast64_t ID = SpellCastingComponentID;
		SpellCastingComponent() : spelltocast_("NO_CAST") { }
		~SpellCastingComponent() {}

		uint_fast64_t UniqueBits() const { return ID; }

		std::string SpellToCast() { return spelltocast_; }
		double CastTime() { return casttime_; }
		double StartTimeOfCast() { return starttimeofcast_; }

		void SetSpellToCast(std::string spelltocast) { spelltocast_ = spelltocast; }
		void SetCastTime(double casttime) { casttime_ = casttime; }
		void SetStartTimeOfCast(double starttimeofcast) { starttimeofcast_ = starttimeofcast; }

	private:
		std::string spelltocast_;
		double casttime_;
		double starttimeofcast_;
};