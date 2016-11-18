#include "Builder.h"
#include "Window.h"

#include <iostream>
#include <fstream>

namespace SAS_GUI {
	namespace Builder {
#define COMMENT '$'
#define NEWITEM '#'

		// Creation methods
		void CreateWindow(Window* activewindow, const std::vector<std::string>& itemproperties) {
			//auto window = std::make_unique<Window>(GetSDLManager(), "mainmenu", SDL_Rect{ 0, 0, 1280, 640 }, "../../../media//backgrounds/charcreationbg.bmp", "../../../media/backgrounds/charcreationbg.bmp", true);

		}

		void CreateTextbox(Window* activewindow, const std::vector<std::string>& itemproperties) {

		}

		void CreateDynamicText(Window* activewindow, const std::vector<std::string>& itemproperties) {

		}

		void CreateButton(Window* activewindow, const std::vector<std::string>& itemproperties) {

		}

		void CreateGUIImage(Window* activewindow, const std::vector<std::string>& itemproperties) {

		}

		void CreateNewItem(std::string item, const std::vector<std::string>& itemproperties, Window* window, GUIManager* guimanager) {
			if (item.empty()) return;

			std::cout << "ITEM: " << item << std::endl;
			for (auto i = 0; i < itemproperties.size(); i++) {
				std::cout << itemproperties[i] << std::endl;
			}
		}

		void BuildGUIFromFile(GUIManager* guimanager, std::string file) {
			Window* activewindow = nullptr;
			std::string activeitemtype = "";
			std::vector<std::string> itemproperties;

			std::ifstream input(file);

			if (!input.good()) {
				std::cout << "Invalid file name : " << file << std::endl;
				input.close();
				return;
			}

			for (std::string line; std::getline(input, line); ) {
				if (line.empty()) continue;
				else if (line[0] == COMMENT) continue; // ignore commented line
				else if (line[0] == NEWITEM) { //Bracket is a new window or component
					CreateNewItem(activeitemtype, itemproperties, activewindow, guimanager);

					activeitemtype = line.substr(1, line.size() - 1);
					itemproperties.clear();
				}
				else
					itemproperties.push_back(line);
			}

			input.close();
		}
	}
}