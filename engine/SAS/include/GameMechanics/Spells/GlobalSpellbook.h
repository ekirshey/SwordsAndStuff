#pragma once
#include <unordered_map>
#include "Types/Spells.h"

// I think I can replace this with just a map... Consider future functionality before removal.
class GlobalSpellbook
{
	public:
		GlobalSpellbook() {}

		void CreateSpell(int spellId, std::string name, int casttime, int cooldown, int duration, std::string graphic, const ScriptedMotion::Script& script) {
			spellbook_.insert({ spellId, Spell(spellId, name, casttime, cooldown, duration, graphic, script) });
		}

		// Returns a copy of a global spell
		Spell GetSpell(int spellId) { 
			return spellbook_[spellId];
		}

	private:
		std::unordered_map<int, Spell> spellbook_;

};

