#pragma once

#include <string>
#include <unordered_map>
#include "../../include/ECSFramework/Component.h"
#include "../Config/ComponentDefines.h"
#include "../Types/Spells.h"

class SpellbookComponent : public Component
{
	public:
		static const uint_fast64_t ID = SpellbookComponentID;
		SpellbookComponent() {}
		~SpellbookComponent() {}

		uint_fast64_t UniqueBits() const { return ID; }

		void AddSpell(Spell spell) { spellbook_[spell.name] = spell; }
		Spell* GetSpell(std::string name) { return &spellbook_[name]; }

	private:
		// Holds spell name and its "description" description might become a custom type and not a string
		std::unordered_map<std::string, Spell> spellbook_;
};

