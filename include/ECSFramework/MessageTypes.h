#pragma once
#include <string>
#include "MessageQueueContainer.h"

const int SPELLMESSAGEID = 0x01;

struct SpellMessage : public Message
{
	uint_fast64_t entity;
	std::string spell;

	int GetID() { return SPELLMESSAGEID; }

	SpellMessage() {}
	SpellMessage(uint_fast64_t entity, std::string spell) : entity(entity), spell(spell) {}
	SpellMessage(const SpellMessage& e) : entity(e.entity),spell(e.spell) {}
};
