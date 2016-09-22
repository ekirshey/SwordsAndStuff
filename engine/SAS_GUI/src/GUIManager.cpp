#include "GUIManager.h"
#include "Input/Input.h"
#include "Rendering/Renderer.h"

namespace SAS_GUI {
	GUIManager::GUIManager()
	{
	}

	GUIManager::~GUIManager()
	{
	}

	void GUIManager::Update(int elapsedtime, const SAS_System::Input& input)
	{
		HandleInput();

		//Update the opened windows
		for (int i = 0; i < windows_.size(); i++) {
			windows_[i]->Update(elapsedtime, input);
		}

	}

	void GUIManager::Render(int elapsedtime, SAS_System::Renderer* renderer) {
		for (int i = 0; i < windows_.size(); i++) {
			windows_[i]->Render(renderer);
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

		if (key != -1) {	//User inputed a key, otherwise it's always open
			GUIKey guikey;
			guikey.window = LastWindow();
			guikey.risingEdge = true;
			keymap_[key] = guikey;
		}

		if ((key == -1) && !LastWindow()->IsOpen())
			std::cout << "WARNING: Window added with no input key and set to always closed. Window will never open" << std::endl;
	}
}