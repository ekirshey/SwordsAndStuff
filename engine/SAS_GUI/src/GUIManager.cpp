#include "GUIManager.h"

namespace SAS_GUI {
	GUIManager::GUIManager()
		: _focusedWindow(nullptr)
		, _focusedComponent(false)
	{
	}

	GUIManager::~GUIManager()
	{
	}

	void GUIManager::Update(int elapsedtime, const SAS_System::Input& input)
	{
		bool hasFocus = false;

		//Update the opened windows
		for (auto& w : _windows) {
			hasFocus ^= w->Update(elapsedtime, input);
		}
		_focusedComponent = hasFocus;
		// Only toggle windows if no other window has keyboard focus
		if (!hasFocus)
			HandleInput(input);
	}

	void GUIManager::Render(SAS_System::Renderer* renderer) {
		for (auto& w : _windows) {
			w->Render(renderer);
		}
	}

	void GUIManager::HandleInput(const SAS_System::Input& input) {
		// If a component has focus then I shouldn't attempt to toggle window focus
		for (auto it = _keymap.begin(); it != _keymap.end(); ++it) {
			if (input.isKeyReleased(it->first))
				it->second->ToggleWindow();
		}

	}

	Window* GUIManager::AddWindow(std::unique_ptr<Window> window, int key) {
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
}