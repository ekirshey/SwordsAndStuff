#pragma once
#include <cstdint>
class ECSManager;
class Spell;

namespace SpellFactory {

	uint_fast64_t CreateSpellEntity(ECSManager* ecsmanager, uint_fast64_t summoner, Spell* spell);
}
