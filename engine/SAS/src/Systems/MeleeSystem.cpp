#include "..\..\include\Systems\MeleeSystem.h"

MeleeSystem::MeleeSystem(std::string systemname, ECSManager* ecsmanager, MessageQueue* messagequeue) :
	QueueSystem(systemname, ecsmanager, messagequeue) {

}


MeleeSystem::~MeleeSystem()
{
}

void MeleeSystem::ProcessMessage(Message* data) {

}

void MeleeSystem::AfterObjectProcessing() {

}