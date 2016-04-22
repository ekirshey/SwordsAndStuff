#include "..\..\include\GUI\GUIManager.h"
#include "..\..\include\SDL\SDLManager.h"

GUIManager::GUIManager() : sdlmanager_(nullptr)
{
}

GUIManager::GUIManager(SDLManager* sdlmanager) : sdlmanager_(sdlmanager)
{

}

GUIManager::~GUIManager()
{
}

void GUIManager::Update(int elapsedtime)
{
	HandleInput();

	//Update the opened windows
	for (int i = 0; i < windows_.size(); i++) {
		windows_[i]->Update(elapsedtime);	
	}

}

void GUIManager::HandleInput() {
	
	auto keyboardstate = sdlmanager_->GetKeyBoardState();

	for (auto it = keymap_.begin(); it != keymap_.end(); ++it) {
		if (!keyboardstate[it->first])
			it->second.risingEdge = true;
		else if (it->second.risingEdge && keyboardstate[it->first]) {
			it->second.window->ToggleWindow();
			it->second.risingEdge = false;
		}
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