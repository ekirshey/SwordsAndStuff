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

		void SendMessage(std::string queuename, Message* data) {
			messagequeues_.at(queuename).AddData(data);
		}

		MessageQueue* GetQueue(std::string queuename) {
			return &messagequeues_.at(queuename);
		}

		void RegisterConsumer(std::string queuename) {
			messagequeues_.at(queuename).RegisterConsumer();
		}

	private:
		std::unordered_map<std::string, MessageQueue> messagequeues_;
};