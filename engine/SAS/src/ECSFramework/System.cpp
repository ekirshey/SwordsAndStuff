#include <algorithm>
#include <iostream>
#include "../../include/ECSFramework/System.h"

System::System() : systemname_(""), ecsmanager_(nullptr), elapsedtime_(0), frametime_(0), entitycount_(0) {

}

System::System(std::string systemname, ECSManager* ecsmanager) : systemname_(systemname), ecsmanager_(ecsmanager), elapsedtime_(0), frametime_(0), entitycount_(0){

}

void System::Update(int elapsedtime) {
	SetFrameTime(elapsedtime);
	UpdateTimeRunning(elapsedtime);

	// Here is where the magic happens
	ProcessEntities();
}

bool System::ValidEntity(uint_fast64_t componentbits, uint_fast64_t SYSTEMID) {
	return ((componentbits & SYSTEMID) == SYSTEMID);
}

void System::AddEntity(uint_fast64_t entityid) {
	// TODO: BE MORE CLEVER maybe find a way that you dont have to loop thru every time you add/remove a component
	if (!ContainsEntity(entityid)) {
		relevantentities_.push_back(entityid);
		entitycount_++;
	}
}

std::vector<uint_fast64_t> System::RelevantEntities() {
	return relevantentities_;
}

void System::RemoveEntity(uint_fast64_t entityid) {
	if (relevantentities_.size() > 0) {
		auto result = std::find(relevantentities_.begin(), relevantentities_.end(), entityid);

		if (result != std::end(relevantentities_)) {
			relevantentities_.erase(result);
			entitycount_--;
		}

	}
}

bool System::ContainsEntity(uint_fast64_t entityid) {
	if (std::find(relevantentities_.begin(), relevantentities_.end(), entityid) != relevantentities_.end())
		return true;
	else
		return false;
}
