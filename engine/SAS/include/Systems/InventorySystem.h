#pragma once
#include "QueueSystem.h"
class InventorySystem : public QueueSystem
{
public:
	InventorySystem(std::string systemname, ECSManager* ecsmanager, MessageQueue* messagequeue);
	~InventorySystem();

	void AfterObjectProcessing();

	void ProcessMessage(Message* data);
private:
};

