#pragma once

#include <string>
#include "ECSFramework/Component.h"
#include "Config/ComponentDefines.h"

#define NO_CAST -1

struct SpellCastingComponent : public Component
{
		static const uint_fast64_t ID = SpellCastingComponentID;
		SpellCastingComponent() : spelltocast(NO_CAST), cancelable(true) { }
		~SpellCastingComponent() {}

		uint_fast64_t UniqueBits() const { return ID; }

		int FindSpellLastCast(int spellid) {
			auto i = lastcastmap.find(spellid);
			if (i != lastcastmap.end()) {
				return i->second;
			}
			else
				return 0;
		}

		void Reset(int currenttime) {
			lastcastmap.insert({spelltocast, currenttime});
			spelltocast = NO_CAST;
		}

		std::unordered_map<int, int> lastcastmap;
		int spelltocast;
		bool cancelable;
		double casttime;
		double starttimeofcast;
};