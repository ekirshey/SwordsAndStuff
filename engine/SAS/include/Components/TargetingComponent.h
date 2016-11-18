#pragma once
#include "ECSFramework/Component.h"
#include "Config/ComponentDefines.h"

#define NOTARGET 0x7FFFFFFFFFFFFFFF

class TargetingComponent : public Component
{
public:
	static const uint_fast64_t ID = TargetingComponentID;

	TargetingComponent() : target_(NOTARGET), hastarget_(false) {}
	TargetingComponent(const TargetingComponent& c) : target_(c.Target()), hastarget_(c.HasTarget()) {}

	~TargetingComponent() {}

	uint_fast64_t UniqueBits() const { return ID; }

	uint_fast64_t Target() const { return target_; }
	bool HasTarget() const { return hastarget_; }

	void SetTarget(uint_fast64_t target) { target_ = target; }
	void SetTargetState(bool hastarget) { hastarget_ = hastarget; }

private:
	uint_fast64_t target_;
	bool hastarget_;
};

