#include "../../include/Systems/InventorySystem.h"
#include "../../include/Components/InventoryComponent.h"
#include "../../include/Types/MessageTypes.h"
#include "../../include/ECSFramework/ECSManager.h"

InventorySystem::InventorySystem(MessageQueue* messagequeue) : QueueSystem(messagequeue) {

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
		auto inventory = &inventorycomponent->inventory_;

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
