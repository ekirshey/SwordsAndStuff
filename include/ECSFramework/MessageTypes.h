#pragma once
#include <string>
#include "MessageQueueContainer.h"


struct SpellMessage : public Message
{
	uint_fast64_t entity;
	std::string spell;

	SpellMessage() {}
	SpellMessage(uint_fast64_t entity, std::string spell) : entity(entity), spell(spell) {}
	SpellMessage(const SpellMessage& e) : entity(e.entity),spell(e.spell) {}
};
