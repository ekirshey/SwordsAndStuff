#pragma once
#include <string>
#include <SDL.h>
#include "GUIMessaging.h"

namespace SAS_GUI {
	struct Cursor {
		bool clear;
		bool locked;
		Payload data;

		Cursor()
			: clear(true)
			, locked(false)
		{

		}

		Cursor(std::string texture, Payload data)
			: clear(true)
			, locked(false)
			, data(data)
		{

		}

		Cursor(const Cursor& p)
			: clear(p.clear)
			, locked(false)
			, data(data)
		{

		}

		Cursor& operator=(const Cursor& other) {
			this->clear = other.clear;
			this->locked = other.locked;
			this->data = data;

			return *this;
		}
	};
}