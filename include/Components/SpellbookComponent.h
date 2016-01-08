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
		SpellbookComponent(const SpellbookComponent& s) : spellbook_(s.spellbook_) {}
		~SpellbookComponent() {}

		uint_fast64_t UniqueBits() const { return ID; }

		void AddSpell(const Spell& spell) { spellbook_[spell.name] = spell; }
		Spell* GetSpell(std::string name) { return &spellbook_[name]; }

	private:
		// String or int??
		// Hold spells somewhere else and store a list of indices?
		std::unordered_map<std::string, Spell> spellbook_;
};

