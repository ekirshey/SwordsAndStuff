#pragma once
#include "../Systems/QueueSystem.h"
#include "../Config/ComponentDefines.h"

class EquipmentSystem : public QueueSystem
{
public:
	EquipmentSystem(MessageQueue* messagequeue);
	~EquipmentSystem();

	void AfterObjectProcessing();

	void ProcessMessage(Message* data);
private:
};

