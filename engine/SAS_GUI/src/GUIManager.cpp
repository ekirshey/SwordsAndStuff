#include "GUIManager.h"

namespace SAS_GUI {
	GUIManager::GUIManager()
		: focusedwindow_(nullptr)
	{
	}

	GUIManager::~GUIManager()
	{
	}

	void GUIManager::Update(int elapsedtime, const SAS_System::Input& input)
	{
		bool hasFocus = false;

		//Update the opened windows
		for (auto& w : windows_) {
			hasFocus ^= w->Update(elapsedtime, input);
		}

		// Only toggle windows if no other window has keyboard focus
		if (!hasFocus)
			HandleInput(input);
	}

	void GUIManager::Render(SAS_System::Renderer* renderer) {
		for (auto& w : windows_) {
			w->Render(renderer);
		}
	}

	void GUIManager::HandleInput(const SAS_System::Input& input) {
		// If a component has focus then I shouldn't attempt to toggle window focus
		for (auto it = keymap_.begin(); it != keymap_.end(); ++it) {
			if (input.isKeyReleased(it->first))
				it->second->ToggleWindow();
		}

	}

	Window* GUIManager::AddWindow(std::unique_ptr<Window> window, int key) {
		windows_.push_back(std::move(window));

		keymap_[key] = windows_.back().get();
		return windows_.back().get();
	}


	Window* GUIManager::GetWindow(std::string windowname) {
		for (auto& w : windows_) {
			if (w->WindowName() == windowname)
				return w.get();
		}

		return nullptr;

	}
}