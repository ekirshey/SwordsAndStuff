#pragma once
#include "MessageQueueContainer.h"

struct EntityMessage : public Message
{
	uint_fast64_t entity;

	EntityMessage() {}
	EntityMessage(uint_fast64_t entity) : entity(entity) {}
	EntityMessage(const EntityMessage& e) : entity(e.entity) {}
};
