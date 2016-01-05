#include "..\..\include\Systems\QueueSystem.h"
#include "..\..\include\ECSFramework\ECSManager.h"	
#include "../../include/ECSFramework/MessageTypes.h"

QueueSystem::QueueSystem( MessageQueue* messagequeue) :messagequeue_(messagequeue) {

	//ecsmanager->GetQueues().RegisterConsumer(queuename_);
	messagequeue->RegisterConsumer();
}


QueueSystem::~QueueSystem() {

}

void QueueSystem::ProcessEntities() {
	//MessageQueue* messagequeue = GetECSManager()->GetQueues().GetQueue(queuename_);

	BeforeObjectProcessing();
	//std::cout << SystemName() << " " << entities.size() << std::endl;
	Message* datum;
	while( (datum = messagequeue_->GetData()) != nullptr) {
		ProcessMessage(datum);

		// Remove message from queue if this is the last registered consumer
		messagequeue_->PopMessage();
	}

	AfterObjectProcessing();
}