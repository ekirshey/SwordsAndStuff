#include "FileParser/cpptoml.h"
#include "GUIBuilder.h"
#include "Window.h"

#include <iostream>

namespace SAS_GUI {
	namespace GUIBuilder {
		SDL_Rect GetRectangle(std::string rectlabel, cpptoml::table* table) {
			auto recttoml = table->get_table(rectlabel);
			int x = recttoml->get_as<int>("x").value_or(0);
			int y = recttoml->get_as<int>("y").value_or(0);
			int width = recttoml->get_as<int>("width").value_or(0);
			int height = recttoml->get_as<int>("height").value_or(0);

			return SDL_Rect{ x, y, width, height };
		}

		void CreateComponent(ComponentDescription* c, cpptoml::table* table) {
			c->name = table->get_as<std::string>("name").value_or("default");
			c->position = GetRectangle("position", table);
		}

		// Creation methods
		void CreateButtons(std::string mediaroot, WindowDescription & wd, cpptoml::table_array* buttontoml) {
			for (const auto& button : *buttontoml) {
				SDL_Rect cliprect = GetRectangle("cliprect", button.get());
				std::string bgtexture = button->get_as<std::string>("bgtexture").value_or("");

				ButtonView bv(cliprect, mediaroot + bgtexture);
				ButtonDescription desc(bv);
				CreateComponent(&desc, button.get());
				wd.buttons.push_back(desc);
			}
		}

		WindowDescription CreateWindow( std::string mediaroot, cpptoml::table* windowtoml) {
			SDL_Rect cliprect = GetRectangle("cliprect", windowtoml);
			std::string bgtexture = windowtoml->get_as<std::string>("bgtexture").value_or("");

			WindowView w(cliprect, mediaroot + bgtexture);

			bool open = windowtoml->get_as<bool>("open").value_or(false);
			WindowDescription desc(w);
			desc.open = open;
			CreateComponent(&desc, windowtoml);

			auto buttons = windowtoml->get_table_array("button");
			CreateButtons(mediaroot, desc, buttons.get());
			
			return desc;
		}

		std::vector<WindowDescription> BuildGUIFromFile(GUIManager* guimanager, std::string mediaroot, std::string file) {
			std::vector<WindowDescription> windowDescriptions;
			// First parse the gui file with cpptoml
			auto guitoml = cpptoml::parse_file(file);

			// Each gui file has an array of windows
			auto windows = guitoml->get_table_array("window");
			for (const auto& window : *windows) {
				std::cout << "Name: " << *window->get_as<std::string>("name") << std::endl;
				windowDescriptions.push_back(CreateWindow(mediaroot, window.get()));			
			}
			
			return windowDescriptions;
		}
	}
}