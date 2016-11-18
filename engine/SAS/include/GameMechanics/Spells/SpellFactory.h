#pragma once
#include <cstdint>
#include "Types/Spells.h"

class ECSManager;

namespace SpellFactory {

	uint_fast64_t CreateSpellEntity(ECSManager* ecsmanager, uint_fast64_t caster, const Spell& spell);
}
