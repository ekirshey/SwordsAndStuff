#pragma once
#include <unordered_map>
#include "Types/Spell.h"

class GlobalSpellbook
{
	public:
		using SpellReference = const Spell const*;
		GlobalSpellbook() {}
		GlobalSpellbook(std::string spellbookfile) {}

		bool CreateSpell(int spellId, std::string name, int casttime, bool cancelable, int cooldown, int duration, std::string graphic, int shapeid, const std::vector<int>& effects) {
			std::vector<SpellComponent*> components;
			for (auto e : effects) {
				auto c = _spellcomponents.find(e);
				if (c != _spellcomponents.end()) {
					components.push_back(c->second.get());
				}
				else {
					std::cout << "Invalid component with id: " << e << std::endl;
					return false;
				}
			}

			auto shape = _spellshapes.find(shapeid);
			if (shape == _spellshapes.end()) {
				std::cout << "invalid spell shape id " << shapeid << std::endl;
				return false;
			}

			_spells.insert({ spellId, Spell(spellId, name, casttime, cancelable, cooldown, duration, graphic, shape->second.get(), components) });
			return true;
		}

		void CreateSpell(int spellId, const Spell& spell) {
			_spells.insert({ spellId, spell });
		}

		template<typename T, typename... Args>
		void CreateSpellComponent(int id, Args&&... args) {
			_spellcomponents.insert({ id, std::make_unique<T>(std::forward<Args>(args)...) });
		}

		template<typename T, typename... Args>
		void CreateSpellShape(int id, Args&&... args) {
			_spellshapes.insert({ id, std::make_unique<T>(std::forward<Args>(args)...) });
		}

		// Returns a const ptr of a const spell
		SpellReference GetSpell(int spellId) {
			auto s = _spells.find(spellId);
			if (s != _spells.end()) {
				return &s->second;
			}
			else
				return nullptr;
		}

	private:
		std::unordered_map<int, std::unique_ptr<SpellShape>> _spellshapes;
		std::unordered_map<int, std::unique_ptr<SpellComponent>> _spellcomponents;
		std::unordered_map<int, const Spell> _spells;


};

