#pragma once
#include <vector>
#include <string>

class Message {
	public:
		virtual ~Message() {}
};

class MessageQueue
{
	public:
		MessageQueue() : consumers_(0), consumed_(0), indextracker_(0) {}

		void AddData(Message* datum) {
			// Dont add data to the queue if we are in the middle of processing
			// Add it to a staging area first
			if (consumers_ > 1 && (consumed_ != 0 || indextracker_ > 0))
				stageddata_.push_front(std::unique_ptr<Message>(std::move(datum)));
			else
			{
				data_.push_front(std::unique_ptr<Message>(std::move(datum)));
				while (stageddata_.size() > 0)
				{
					data_.push_front(std::move(stageddata_.front()));
					stageddata_.pop_front();
				}

			}
		}

		bool Empty() { return data_.size(); }

		Message* GetData() {
			Message* data = nullptr;

			if (consumed_ == (consumers_ - 1)) {
				if (!data_.empty()) {
					data = data_.front().get();
					data_.pop_front();
				}
				else
					consumed_ = 0;
			}
			else if (!data_.empty()) {
				if (indextracker_ < data_.size()) {
					data = data_[indextracker_++].get();
				}
				else {
					consumed_++;
					indextracker_ = 0;
				}
			}

			return data;
		}

		void RegisterConsumer() { consumers_++; }

	private:
		std::deque<std::unique_ptr<Message>> data_;
		std::deque<std::unique_ptr<Message>> stageddata_;
		int consumers_;
		int consumed_;
		int indextracker_;

};

