#pragma once

#include <string>
#include "ECSFramework/Component.h"
#include "Config/ComponentDefines.h"

#define NO_CAST -1

// NOTE: Determine actual spell format
class SpellCastingComponent : public Component
{
	public:
		static const uint_fast64_t ID = SpellCastingComponentID;
		SpellCastingComponent() : spelltocast_(NO_CAST), cancelable_(true) { }
		~SpellCastingComponent() {}

		uint_fast64_t UniqueBits() const { return ID; }

		int SpellToCast() { return spelltocast_; }
		double CastTime() { return casttime_; }
		double StartTimeOfCast() { return starttimeofcast_; }
		bool Cancelable() { return cancelable_;  }

		void SetSpellToCast(int spelltocast) { spelltocast_ = spelltocast; }
		void SetCastTime(double casttime) { casttime_ = casttime; }
		void SetStartTimeOfCast(double starttimeofcast) { starttimeofcast_ = starttimeofcast; }
		void SetCancelable(bool cancelable) { cancelable_ = cancelable;  }

	private:
		int spelltocast_;
		bool cancelable_;
		double casttime_;
		double starttimeofcast_;
};