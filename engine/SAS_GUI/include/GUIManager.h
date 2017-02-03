#pragma once
#include <vector>
#include <map>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include "GUIComponents/Window.h"
#include "Input/Input.h"
#include "Rendering/Renderer.h"
#include "GUIMessaging.h"

namespace SAS_GUI {

	#define MAXMESSAGES 100
	/*
	If a window is added without an associated key, then it's assumed the window will always be in it's initial state
	*/
	class GUIManager
	{
	public:
		GUIManager();
		~GUIManager();

		void Update(int elapsedtime,const SAS_System::Input& input);
		void Render(SAS_System::Renderer* renderer);

		//returns pointer to the moved window
		Window* AddWindow(std::unique_ptr<Window> window, int key = -1);

		Window* GetWindow(std::string windowname);

		bool GUIHasFocus();

		void ReceiveMessage(const Message& msg);

	private:
		void HandleInput(const SAS_System::Input& input);
		std::vector<std::unique_ptr<Window>> _windows;
		std::vector<Message> _receivedMessages;
		std::vector<Message> _internalMessages;
		std::vector<Message> _externalMessages;
		int _messageCount;
		std::unordered_map<int, Window*> _keymap;
		Payload _cursor;
		SDL_Point _cursorcoords;
		bool _displayCursor;

		Window* _focusedWindow;
		bool _focusedComponent;
	};

}
