#pragma once
#include "Input/Input.h"
#include "Rendering/Renderer.h"
#include "GUIMessaging.h"
#include "Cursor.h"


namespace SAS_GUI {
	class Component
	{

	public:
		virtual void Update(const SDL_Rect& windowrect, const SAS_System::Input& input, bool& hasFocus, int elapsedtime) = 0;
		virtual void Render(SAS_System::Renderer* renderer) = 0;
		
		// Optional function for handling the shared gui cursor
		virtual void RegisterCursor(Cursor* payload) {}

		// Optional Messaging functions
		virtual void ReceiveMessages(const std::vector<Message>& messages, int messagect) {}
		virtual void SendExternalMessage(std::vector<Message>* messages) {}

		virtual ~Component() {}
	};

}
