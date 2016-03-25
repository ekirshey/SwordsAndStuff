#pragma once
#include <deque>
#include <unordered_map>
#include <string>
#include <iostream>
#include <memory>
#include "MessageQueue.h"

class MessageQueueContainer
{
	public:
		MessageQueueContainer() {}
		~MessageQueueContainer() {}

		void AddQueue(std::string queuename) {
			messagequeues_.insert({ queuename, MessageQueue() });
		}

		template<typename T, typename... Args>
		void SendMessage(std::string queuename, Args... args) {
			messagequeues_.at(queuename).AddData(std::make_unique<T>( args... ) );
		}

		MessageQueue* GetQueue(std::string queuename) {
			auto queue = messagequeues_.find(queuename);

			if (queue != messagequeues_.end()) {
				return &queue->second;
			}
			else {
				std::cout << "Invalid Queue Name: " << queuename << std::endl;
				return nullptr;
			}
		}

		void RegisterConsumer(std::string queuename) {
			messagequeues_.at(queuename).RegisterConsumer();
		}

	private:
		std::unordered_map<std::string, MessageQueue> messagequeues_;
};