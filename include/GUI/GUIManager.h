#pragma once
#include <vector>
#include <map>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include "GUIComponents/GUIWindow.h"

class SDLManager;

struct GUIKey {
	GUIWindow* window;
	bool risingEdge;
};
/*
If a window is added without an associated key, then it's assumed the window will always be in it's initial state
*/
class GUIManager
{
	public:
		GUIManager();
		GUIManager(SDLManager* sdlmanager);
		~GUIManager();

		void Update(int elapsedtime);
	
		void AddWindow(std::unique_ptr<GUIWindow> window, int key = -1);

	private:
		GUIWindow* LastWindow() { return windows_.back().get(); }

		void HandleInput();
		std::vector<std::unique_ptr<GUIWindow>> windows_;
		std::unordered_map<int, GUIKey> keymap_;
		SDLManager* sdlmanager_;
};


