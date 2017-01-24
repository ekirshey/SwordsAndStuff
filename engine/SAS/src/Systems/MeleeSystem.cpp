#include "Systems\MeleeSystem.h"
#include "Types/MessageTypes.h"

MeleeSystem::MeleeSystem(std::string systemname, ECSManager* ecsmanager, MessageQueue* messagequeue) :
	QueueSystem(systemname, ecsmanager, messagequeue) {

}


MeleeSystem::~MeleeSystem()
{
}

void MeleeSystem::ProcessMessage(Message* data) {

	if (data->GetID() == MELEEMESSAGEID) {
		auto msg = static_cast<MeleeMessage*>(data);

	}
}

void MeleeSystem::AfterObjectProcessing() {

}