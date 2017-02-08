#pragma once

#include <string>
#include <unordered_map>
#include "ECSFramework/Component.h"
#include "Config/ComponentDefines.h"
#include "Types/Spell.h"
#include "GameMechanics/Spells/GlobalSpellbook.h"

class SpellbookComponent : public Component
{
	public:
		static const uint_fast64_t ID = SpellbookComponentID;
		SpellbookComponent() {}
		SpellbookComponent(const SpellbookComponent& s) : _spellbook(s._spellbook) {}
		~SpellbookComponent() {}

		uint_fast64_t UniqueBits() const { return ID; }

		void AddSpell(int spellId, GlobalSpellbook::SpellReference spell) {
			_spellbook.insert({ spellId, spell });
		}

		GlobalSpellbook::SpellReference GetSpell(int id) { 
			return _spellbook[id]; 
		}

	private:
		std::unordered_map<int, GlobalSpellbook::SpellReference> _spellbook;
};

