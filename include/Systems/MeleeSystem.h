#pragma once
#include "../Systems/QueueSystem.h"
#include "../Config/ComponentDefines.h"

class MeleeSystem : public QueueSystem
{
public:
	MeleeSystem(MessageQueue* messagequeue);
	~MeleeSystem();

	void AfterObjectProcessing();

	void ProcessMessage(Message* data);

private:
	std::vector<uint_fast64_t> meleeattacks_;
};
