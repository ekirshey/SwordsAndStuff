#pragma once

#include "ECSFramework/Component.h"
#include "Config/ComponentDefines.h"

struct TTLComponent : public Component
{
	static const uint_fast64_t ID = TTLComponentID;

	TTLComponent(int ttl, int timecreated) :_ttl(ttl), _timecreated(timecreated) {}
	TTLComponent(const TTLComponent& c) : _ttl(c._ttl), _timecreated(c._timecreated) {}

	~TTLComponent() {}

	uint_fast64_t UniqueBits() const {return ID;}

	int _ttl;	//time to live in ms
	int _timecreated;
};


