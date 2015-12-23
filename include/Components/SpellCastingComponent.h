#pragma once

#include <string>
#include "../../include/ECSFramework/Component.h"
#include "../Config/ComponentDefines.h"

// NOTE: Determine actual spell format
class SpellCastingComponent : public Component
{
	public:
		static const uint_fast64_t ID = SpellCastingComponentID;
		SpellCastingComponent() : spelltocast_("NO_CAST") { }
		virtual ~SpellCastingComponent() {}
	private:
		std::string spelltocast_;
		double casttime_;
		double starttimeofcast_;
};