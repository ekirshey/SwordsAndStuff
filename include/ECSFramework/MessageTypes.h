#pragma once
#include <string>
#include "MessageQueueContainer.h"

const int SPELLMESSAGEID = 0x01;

struct SpellMessage : public Message
{
	uint_fast64_t entity;
	int spellId;

	int GetID() { return SPELLMESSAGEID; }

	SpellMessage() {}
	SpellMessage(uint_fast64_t entity, int spellId) : entity(entity), spellId(spellId) {}
	SpellMessage(const SpellMessage& e) : entity(e.entity), spellId(e.spellId) {}
};
