#include "..\..\include\Systems\EquipmentSystem.h"
#include "../../include/Components/EquipmentComponent.h"
#include "../../include/Types/MessageTypes.h"
#include "../../include/ECSFramework/ECSManager.h"

EquipmentSystem::EquipmentSystem(MessageQueue* messagequeue) : QueueSystem(messagequeue) {

}

EquipmentSystem::~EquipmentSystem() {

}

void EquipmentSystem::AfterObjectProcessing() {

}

void EquipmentSystem::ProcessMessage(Message* data) {
	// Check for valid item message
	if (data->GetID() == ITEMMESSAGEID) {
		auto msg = static_cast<ItemMessage*>(data);
		auto inventorycomponent = GetEntityComponent<EquipmentComponent*>(msg->entity, EquipmentComponent::ID);

	}
}