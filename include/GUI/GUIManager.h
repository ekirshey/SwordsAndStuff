#pragma once
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include "GUIComponents/GUIWindow.h"

class SDLManager;

class GUIManager
{
public:
	GUIManager();
	GUIManager(SDLManager* sdlmanager, std::string keymapfile, std::string guifile);
	~GUIManager();

	void Update();

private:
	void Initialize(std::string keymapfile, std::string guifile);
	std::vector<std::unique_ptr<GUIWindow>> windows_;
	std::vector<int> openwindows_;
	std::unordered_map<uint8_t, int> guikeymap_;
	SDLManager* sdlmanager_;
};

/*
have buttons linked to window names which are then linked to the indices
C "Character Window"
At initialization find window in window vector that is called character window and at it into a map
KEY, WINDOW INDEX

*/

