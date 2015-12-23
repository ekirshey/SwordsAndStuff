#pragma once

#include <string>
#include <unordered_map>
#include "../../include/ECSFramework/Component.h"
#include "../Config/ComponentDefines.h"


class SpellbookComponent : public Component
{
	public:
		static const uint_fast64_t ID = SpellbookComponentID;
		SpellbookComponent() {}
		~SpellbookComponent() {}

	private:
		// Holds spell name and its "description" description might become a custom type and not a string
		std::unordered_map<std::string, std::string> spellbook_;
};

