#pragma once
#include "..\ECSFramework\System.h"

class MessageQueue;
class Message;

class QueueSystem : public System
{
	public:
		QueueSystem(std::string systemname, ECSManager* ecsmanager, MessageQueue* messagequeue);
		~QueueSystem();

		virtual void ProcessMessage(Message* data) = 0;
		void ProcessEntities();

		virtual void BeforeObjectProcessing() {}
		virtual void AfterObjectProcessing() {}

	private:
		MessageQueue* messagequeue_;
};

