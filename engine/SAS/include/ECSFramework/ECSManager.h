#ifndef ECSManager_H
#define ECSManager_H

#include <memory>
#include <unordered_map>
#include <vector>
#include <string>
#include "SystemManager.h"
#include "EntityManager.h"
#include "MessageQueueContainer.h"

class ECSManager
{
    public:
        ECSManager();
        virtual ~ECSManager();

        int AddSystem(std::unique_ptr<System> system, int priority);

		// Use std::forward to maintain lvalue and rvalue references
		template<typename T, typename... Args>
		int AddSystem( std::string systemname, int priority, Args&&... args) {
			auto system = std::make_unique<T>(systemname, this, std::forward<Args>(args)...);
			return systemmanager_.AddSystem(std::move(system), priority);
		}

		System* GetSystem(int systemid);

        uint_fast64_t CreateEntity();
        void RemoveEntity(uint_fast64_t entity);

		template<class T> 
		T GetEntityComponent(uint_fast64_t entity, uint_fast64_t componentid) {
			return static_cast<T>(entitymanager_.GetEntityComponent(entity, componentid));
		}

        std::vector<Component*> GetAllEntityComponents(uint_fast64_t entity);

		uint_fast64_t GetEntityComponentBits(uint_fast64_t entity) { return entitymanager_.GetEntityComponentBits(entity); }
		uint_fast64_t EntityCount() { return entitymanager_.EntityCount(); }

        void AddComponentToEntity(uint_fast64_t entity, std::unique_ptr<Component> componenttoadd);

		template<typename T, typename... Args>
		void AddComponentToEntity(uint_fast64_t entity, Args&&... args) {
			auto c = std::make_unique<T>(std::forward<Args>(args)...);
			if ( entitymanager_.AddComponent( entity, std::move(c) ) )
				systemmanager_.AddEntityToSystem(entity, entitymanager_.GetEntityComponentBits(entity));
		}

        void RemoveComponentFromEntity(uint_fast64_t entity, uint_fast64_t componentid);

        void Update(int elapsedtime);

        // Tag functions    TODO Should these be in an object? Idk it will just double the function calls, who cares?
		void ClearTagVector(std::string tag);
        void AssignEntityTag(uint_fast64_t entity,std::string tag);
        void RemoveEntityFromTag(uint_fast64_t entity,std::string tag);
        void RemoveTag(std::string tag);
        void AddTag(std::string tag);
        std::vector<std::string> GetAssociatedTags(uint_fast64_t entity);
        std::vector<uint_fast64_t> GetAssociatedEntities(std::string tag);
        std::vector<uint_fast64_t>* GetPtrToAssociatedEntities(std::string tag) {return &tagmanager_[tag];}

		MessageQueue* GetQueue(std::string queue) { 
			return messagequeuecontainer_.GetQueue(queue); 
		}
		void AddQueue(std::string queue) { messagequeuecontainer_.AddQueue(queue); }

		template<typename T, typename... Args>
		void SendMessage(std::string queuename, Args&&... args) {
			messagequeuecontainer_.SendMessage<T>(queuename, std::forward<Args>(args)...);
		}

		void Exit(int code) {
			std::cout << "Exiting ECSManager with Code " << code << std::endl;
			errorcode_ = code;
			status_ = false;
		}

		bool GetStatus(int& errorcode) {
			errorcode = errorcode_;
			return status_;
		}

    private:
		bool status_;
		int errorcode_;
        SystemManager systemmanager_;
        EntityManager entitymanager_;
		MessageQueueContainer messagequeuecontainer_;
        std::unordered_map<std::string,std::vector<uint_fast64_t>> tagmanager_;
};

#endif // ECSManager_H
