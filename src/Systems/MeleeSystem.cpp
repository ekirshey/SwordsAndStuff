#include "..\..\include\Systems\MeleeSystem.h"

MeleeSystem::MeleeSystem(MessageQueue* messagequeue) : QueueSystem(messagequeue) {
	SetSystemName("MeleeSystem");
}


MeleeSystem::~MeleeSystem()
{
}

void MeleeSystem::ProcessMessage(Message* data) {

}

void MeleeSystem::AfterObjectProcessing() {

}