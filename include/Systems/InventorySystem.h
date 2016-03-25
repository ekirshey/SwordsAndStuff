#pragma once
#include "QueueSystem.h"
class InventorySystem : public QueueSystem
{
public:
	InventorySystem(MessageQueue* messagequeue);
	~InventorySystem();

	void AfterObjectProcessing();

	void ProcessMessage(Message* data);
private:
};

