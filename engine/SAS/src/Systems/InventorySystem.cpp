#include "Systems/InventorySystem.h"
#include "Components/InventoryComponent.h"
#include "Types/MessageTypes.h"
#include "ECSFramework/ECSManager.h"

InventorySystem::InventorySystem(std::string systemname, ECSManager* ecsmanager, MessageQueue* messagequeue) : 
	QueueSystem(systemname, ecsmanager, messagequeue) {

}

InventorySystem::~InventorySystem() {

}

void InventorySystem::AfterObjectProcessing() {

}

void InventorySystem::ProcessMessage(Message* data) {

	// Check for valid item message
	if (data->GetID() == ITEMMESSAGEID) {
		auto msg = static_cast<ItemMessage*>(data);
		auto inventorycomponent = GetEntityComponent<InventoryComponent*>(msg->entity, InventoryComponent::ID);
		auto inventory = &inventorycomponent->inventor_y;

		if (inventory->size() < inventorycomponent->maxinventorysize_) {
			// Add to specific slot if one was specified
			if (msg->destinationslot < inventory->size() && msg->destinationslot > 0) {
				if (inventory->at(msg->destinationslot) == nullptr) {
					inventory->at(msg->destinationslot) = msg->item;
				}
				else {
					////// Handle case where something is in the slot
					std::cout << "Something exists in the slot. How do we handle this?" << std::endl;
				}
			}
			else {
				inventory->push_back(msg->item);
			}
			
			msg->item->owner_ = msg->entity;
		}
	}
	
}
