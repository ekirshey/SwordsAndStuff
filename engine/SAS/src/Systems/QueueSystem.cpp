#include "..\..\include\Systems\QueueSystem.h"
#include "..\..\include\ECSFramework\ECSManager.h"	
#include "../../include/Types/MessageTypes.h"

QueueSystem::QueueSystem(std::string systemname, ECSManager* ecsmanager, MessageQueue* messagequeue) : 
	System(systemname, ecsmanager), messagequeue_(messagequeue) {

	if (messagequeue != nullptr) {
		messagequeue->RegisterConsumer();
	}
	else {
		std::cout << "Bad message queue in " << SystemName() << std::endl;
	}

}


QueueSystem::~QueueSystem() {

}

void QueueSystem::ProcessEntities() {
	//MessageQueue* messagequeue = GetECSManager()->GetQueues().GetQueue(queuename_);

	BeforeObjectProcessing();

	Message* datum;
	while( (datum = messagequeue_->GetData()) != nullptr) {
		ProcessMessage(datum);

		// Remove message from queue if this is the last registered consumer
		messagequeue_->PopMessage();
	}

	AfterObjectProcessing();
}