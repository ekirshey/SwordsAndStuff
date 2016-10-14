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
		HandleInput(input);

		//Update the opened windows
		for (auto& w : windows_) {
			w->Update(elapsedtime, input);
		}
	}

	void GUIManager::Render(SAS_System::Renderer* renderer) {

		for (auto& w : windows_) {
			w->Render(renderer);
		}
	}

	void GUIManager::HandleInput(const SAS_System::Input& input) {

		for (auto it = keymap_.begin(); it != keymap_.end(); ++it) {
			if (input.isKeyReleased(it->first))
				it->second->ToggleWindow();
		}

	}

	void GUIManager::AddWindow(std::unique_ptr<GUIWindow> window, int key) {
		windows_.push_back(std::move(window));

		keymap_[key] = windows_.back().get();
		
	}
}