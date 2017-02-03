#include "GUIManager.h"

namespace SAS_GUI {
	GUIManager::GUIManager()
		: _receivedMessages(MAXMESSAGES)
		, _internalMessages(MAXMESSAGES)
		, _externalMessages(MAXMESSAGES)
		, _messageCount(0)
		, _displayCursor(false)
		, _focusedWindow(nullptr)
		, _focusedComponent(false)
	{
	}

	GUIManager::~GUIManager()
	{
	}

	void GUIManager::Update(int elapsedtime, const SAS_System::Input& input)
	{
		_internalMessages.clear();
		bool hasFocus = false;
		int x, y;
		input.getMouseState(x, y);
		// Update Cursor position
		if (_displayCursor) {
			_cursorcoords.x = x;
			_cursorcoords.y = y;
		}

		//Update the opened windows
		for (auto& w : _windows) {
			hasFocus ^= w->Update(elapsedtime, input, _receivedMessages, _messageCount);
		}
		_messageCount = 0;

		_focusedComponent = hasFocus;
		// Only toggle windows if no other window has keyboard focus
		if (!hasFocus)
			HandleInput(input);

		for (auto& m : _internalMessages) {
			if (m.destid == GUIMANAGERID) {
				if ( m.data.type == CURSORTYPE) {
					if (m.messagetype == MESSAGETYPE::ADD) {
						_cursor = m.data;
						_displayCursor = true;
						_cursorcoords.x = x;
						_cursorcoords.y = y;
					}
					else if (m.messagetype == MESSAGETYPE::DELETE) {
						_displayCursor = false;
					}
				}
			}
		}
	}

	void GUIManager::Render(SAS_System::Renderer* renderer) {
		for (auto& w : _windows) {
			w->Render(renderer);
		}

		if (_displayCursor) {
			renderer->RenderImage(_cursor.texture, _cursorcoords.x, _cursorcoords.y, &_cursor.cliprect);
		}
	}

	void GUIManager::HandleInput(const SAS_System::Input& input) {
		// If a component has focus then I shouldn't attempt to toggle window focus
		for (auto it = _keymap.begin(); it != _keymap.end(); ++it) {
			if (input.isKeyPressed(it->first))
				it->second->ToggleWindow();
		}

	}

	Window* GUIManager::AddWindow(std::unique_ptr<Window> window, int key) {
		window->_registerInternalGUIQueue(&_internalMessages);
		window->_registerExternalGUIQueue(&_externalMessages);
		_windows.push_back(std::move(window));

		_keymap[key] = _windows.back().get();
		return _windows.back().get();
	}


	Window* GUIManager::GetWindow(std::string windowname) {
		for (auto& w : _windows) {
			if (w->WindowName() == windowname)
				return w.get();
		}

		return nullptr;
	}

	bool GUIManager::GUIHasFocus() {
		return _focusedComponent;
	}

	void GUIManager::ReceiveMessage(const Message& msg) {
		_receivedMessages[_messageCount++] = msg;
	}
}