#pragma once
#include <vector>
#include <string>

class Message {
	public:
		virtual ~Message() {}
		virtual int GetID() = 0;
};

class MessageQueue
{
	public:
		MessageQueue() : consumers_(0), consumed_(0), indextracker_(0) {}

		void AddData(std::unique_ptr<Message> datum) {
			// Dont add data to the queue if we are in the middle of processing
			// Add it to a staging area first
			if (consumers_ > 1 && (consumed_ != 0 || indextracker_ > 0)) {
				stageddata_.push_front(std::move(datum));
			}
			else
			{
				data_.push_front(std::move(datum));
				while (stageddata_.size() > 0)
				{
					data_.push_front(std::move(stageddata_.front()));
					stageddata_.pop_front();
				}

			}
		}

		bool Empty() { return data_.empty(); }

		Message* GetData() {
			Message* data = nullptr;

			if (indextracker_ < data_.size()) {
				data = data_[indextracker_++].get();
			}
			else if (indextracker_ > 0) {
				consumed_++;
				if (data_.empty())
					consumed_ = 0;
				indextracker_ = 0;
			}


			return data;
		}

		// Handle removing the message, if needed.
		// This was split from GetData due to the inability of returning a raw pointer
		// or a unique_ptr. I ended up destroying data before accessing it
		void PopMessage()
		{
			if (consumed_ == (consumers_-1)) {
				if (!data_.empty()) {
					data_.pop_front();
				}
			}
		}

		void RegisterConsumer() { consumers_++; }

	private:
		std::deque<std::unique_ptr<Message>> data_;
		std::deque<std::unique_ptr<Message>> stageddata_;
		int consumers_;
		int consumed_;
		int indextracker_;

};

