#pragma once

#include "Component.h"

namespace SAS_GUI {
	template<typename T>
	class ValueComponent : public Component {
		public:
			virtual T GetValue() = 0;
			~ValueComponent() {}
	};
}