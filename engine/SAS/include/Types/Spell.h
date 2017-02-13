#pragma once
#include "SpellComponent.h"
#include "Components/RenderComponent.h"
#include "Components/TTLComponent.h"

// Master copy of each spell lives in the Global Spellbook
class Spell {
	public:
		Spell(int spellId, std::string name, int casttime, bool cancelable, int cooldown, int duration, std::string graphic, SpellShape* shape, const std::vector<SpellComponent*>& effects)
			: _name(name)
			, _casttime(casttime)
			, _cancelable(cancelable)
			, _cooldown(cooldown)
			, _duration(duration)
			, _graphic(graphic)
			, _spellshape(shape)
			, _spellcomponents(effects)
		{
		}

		std::string Name() const {
			return _name;
		}

		int Casttime() const {
			return _casttime;
		}

		bool isCancelable() const {
			return _cancelable;
		}

		int Cooldown() const {
			return _cooldown;
		}

		int Duration() const {
			return _duration;
		}

		void CreateSpell(ECSManager* ecsmanager, uint_fast64_t caster, int currenttime) const{
			auto createdentities = _spellshape->CreateSpellEntities(ecsmanager, caster);

			for (auto id : createdentities) {
				SDL_Rect rect = { 0,0,16,16 };

				for (auto sc : _spellcomponents) {
					sc->SetEntityComponents(ecsmanager, id, caster);
				}
				ecsmanager->AddComponentToEntity<TTLComponent>(id, _duration, currenttime);
				ecsmanager->AddComponentToEntity<RenderComponent>(id, _graphic, rect);
			}
		}

	private:
		const std::string _name;
		const int _casttime;
		const bool _cancelable;
		const int _cooldown;
		const int _duration;
		std::string _graphic; // This should and will probably be set by the spellshape component

		SpellShape* _spellshape;
		std::vector<SpellComponent*> _spellcomponents;
};
