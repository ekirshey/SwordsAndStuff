#pragma once
#include <unordered_map>
#include "../../Types/Spells.h"

// I think I can replace this with just a map... Consider future functionality before removal.
class GlobalSpellbook
{
	public:
		GlobalSpellbook() {}

		Spell CreateSpell(std::string name, int casttime, int cooldown, int duration, std::string graphic) {
			spellbook_[name] = Spell(name, casttime, cooldown, duration, graphic);
			return spellbook_[name];
		}

		// Returns a copy of a global spell
		Spell GetSpell(std::string name) { return spellbook_[name]; }

	private:
		std::unordered_map<std::string, Spell> spellbook_;

};

