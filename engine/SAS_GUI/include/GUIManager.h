#pragma once
#include <vector>
#include <map>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include "GUIComponents/GUIWindow.h"
#include "Input/Input.h"
#include "Rendering/Renderer.h"

namespace SAS_GUI {

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

		void AddWindow(std::unique_ptr<GUIWindow> window, int key = -1);

	private:
		void HandleInput(const SAS_System::Input& input);
		std::vector<std::unique_ptr<GUIWindow>> windows_;
		std::unordered_map<int, GUIWindow*> keymap_;
	};

}
