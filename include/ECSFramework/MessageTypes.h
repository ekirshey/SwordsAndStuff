#pragma once
#include <string>
#include "MessageQueueContainer.h"
#include "../Types/Items.h"

const int SPELLMESSAGEID = 0x01;
const int MELEEMESSAGEID = 0x02;
const int ADDITEMMESSAGEID = 0x03;
const int REMOVEITEMMESSAGEID = 0x04;

struct SpellMessage : public Message
{
	uint_fast64_t entity;
	int spellId;

	int GetID() { return SPELLMESSAGEID; }

	SpellMessage() {}
	SpellMessage(uint_fast64_t entity, int spellId) : entity(entity), spellId(spellId) {}
	SpellMessage(const SpellMessage& e) : entity(e.entity), spellId(e.spellId) {}
};

struct MeleeMessage : public Message
{
	uint_fast64_t entity;
	int meleeId;

	int GetID() { return MELEEMESSAGEID; }

	MeleeMessage() {}
	MeleeMessage(uint_fast64_t entity, int spellId) : entity(entity), meleeId(meleeId) {}
	MeleeMessage(const MeleeMessage& e) : entity(e.entity), meleeId(e.meleeId) {}
};

struct ItemMessage : public Message {
	int operation;
	std::unique_ptr<Item> item;
	int GetID() { return operation; }

	ItemMessage() : item(nullptr), operation(-1) { }
	ItemMessage(int operation, std::unique_ptr<Item> item) : item(std::move(item)), operation(operation) { }
};



