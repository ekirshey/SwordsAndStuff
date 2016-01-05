#pragma once
#include <vector>
#include "AITemplate.h"

struct ScriptedEvent{
	int destinationX;
	int destinationY;

};

class AIScripted : public AITemplate {
	public:
		AIScripted() {}
		AIScripted(std::vector<ScriptedEvent> v) : scriptedevents_(v) {}
	private:
		std::vector<ScriptedEvent> scriptedevents_;
};

