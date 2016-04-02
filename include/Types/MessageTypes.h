#pragma once
#include <string>
#include "../ECSFramework/MessageQueueContainer.h"
#include "../Types/Items.h"

const int SPELLMESSAGEID = 0x01;
const int MELEEMESSAGEID = 0x02;
const int ITEMMESSAGEID = 0x03;

enum ItemOperation { ADDITEM, REMOVE };

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
	uint_fast64_t entity;
	Items::Item* item;
	int destinationslot;

	int GetID() { return ITEMMESSAGEID; }

	ItemMessage(uint_fast64_t entity, Items::Item* item, int operation, int destinationslot) : entity(entity), item(item), operation(operation), destinationslot(destinationslot) { }
	ItemMessage(uint_fast64_t entity, Items::Item* item, int operation) : entity(entity), item(item), operation(operation), destinationslot(-1) { }
};


