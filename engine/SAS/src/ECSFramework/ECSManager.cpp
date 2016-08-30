#include <algorithm>
#include <iostream>
#include "../../include/ECSFramework/ECSManager.h"
#include "../../include/ECSFramework/System.h"


ECSManager::ECSManager() : status_(true), errorcode_(1) {
    
}

ECSManager::~ECSManager() {
    //dtor
}


int ECSManager::AddSystem(std::unique_ptr<System> system, int priority) {
	//system->SetECSManager(this);
	return systemmanager_.AddSystem(std::move(system),priority);
}


System* ECSManager::GetSystem(int systemid) {
	return systemmanager_.GetSystem(systemid);
}

uint_fast64_t ECSManager::CreateEntity() {
    return entitymanager_.GetNewEntityUUID();
}

void ECSManager::RemoveEntity(uint_fast64_t entity) {
    std::vector<std::string> entitytags;
    entitymanager_.RemoveEntity(entity);
    systemmanager_.RemoveEntityFromSystems(entity);

    entitytags = GetAssociatedTags(entity);

    for (unsigned int i = 0; i < entitytags.size(); i++)
        RemoveEntityFromTag(entity,entitytags[i]);
}

std::vector<Component*> ECSManager::GetAllEntityComponents(uint_fast64_t entity) {
    return entitymanager_.GetAllEntityComponents(entity);
}

void ECSManager::AddComponentToEntity(uint_fast64_t entity, std::unique_ptr<Component> componenttoadd) {
    if ( entitymanager_.AddComponent(entity, std::move(componenttoadd)) )
        systemmanager_.AddEntityToSystem(entity, entitymanager_.GetEntityComponentBits(entity));
}


void ECSManager::RemoveComponentFromEntity(uint_fast64_t entity, uint_fast64_t componentid) {
    if ( entitymanager_.RemoveComponent(entity,componentid) )
        systemmanager_.RemoveEntityFromSystems(entity, entitymanager_.GetEntityComponentBits(entity));
}

void ECSManager::Update(int elapsedtime) {
    systemmanager_.Update(elapsedtime);
}

// Tag functions
void ECSManager::AssignEntityTag(uint_fast64_t entity,std::string tag) {
	tagmanager_[tag].push_back(entity);
}

void ECSManager::RemoveEntityFromTag(uint_fast64_t entity,std::string tag) {
    auto result = std::find(tagmanager_[tag].begin(),tagmanager_[tag].end(),entity);

    if (result != std::end(tagmanager_[tag]))
        tagmanager_[tag].erase(result);
}

void ECSManager::RemoveTag(std::string tag) {
    tagmanager_.erase(tag);
}

void ECSManager::AddTag(std::string tag) {
    if (tagmanager_.find(tag) == tagmanager_.end())
        tagmanager_[tag] = std::vector<uint_fast64_t>();
}

std::vector<std::string> ECSManager::GetAssociatedTags(uint_fast64_t entity) {
    std::vector<std::string> tags;
    for (auto it: tagmanager_) {
        auto result = std::find(it.second.begin(),it.second.end(),entity);
        if (result != std::end(it.second))
            tags.push_back(it.first);
    }

    return tags;
}

void ECSManager::ClearTagVector(std::string tag) {
	tagmanager_[tag].clear();
}

std::vector<uint_fast64_t> ECSManager::GetAssociatedEntities(std::string tag) {
    return tagmanager_[tag];
}
