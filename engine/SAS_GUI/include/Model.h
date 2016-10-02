#pragma once
#include <string>

namespace SAS_GUI {
	class Model {
		public:
			virtual ~Model() {}
			virtual const std::string& getValue(int key) = 0;
			virtual void callFunction(int key) = 0;
			virtual void updateValue(int key, std::string value) = 0;
	};
}

