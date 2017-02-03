#include <functional>
#include "FileParser/cpptoml.h"
#include "GUIBuilder.h"
#include "Window.h"
#include "Button.h"

#include <iostream>

namespace SAS_GUI {
	namespace GUIBuilder {
		std::unordered_map<std::string, BUTTON_TASKS> tasks_map = {
			{"OPEN", BUTTON_TASKS::OPEN},
			{"CLOSE", BUTTON_TASKS::CLOSE},
			{"TOGGLE", BUTTON_TASKS::TOGGLE},
			{"DISABLE", BUTTON_TASKS::DISABLE},
			{"UNDISABLE", BUTTON_TASKS::UNDISABLE},
		};

		std::unordered_map<std::string, TASK_TARGETS> task_target_map = {
			{"WINDOW", TASK_TARGETS::WINDOW},
			{"BUTTON", TASK_TARGETS::BUTTON},
		};

		SDL_Rect GetRectangle(std::string rectlabel, cpptoml::table* table) {
			auto recttoml = table->get_table(rectlabel);
			int x = recttoml->get_as<int>("x").value_or(0);
			int y = recttoml->get_as<int>("y").value_or(0);
			int width = recttoml->get_as<int>("width").value_or(0);
			int height = recttoml->get_as<int>("height").value_or(0);

			return SDL_Rect{ x, y, width, height };
		}

		/* Limited configuration options for setting button tasks.
		   The button can be set to control other gui features from the config script. If a non-gui related
		   button action is needed, then it's up to the user to pass in an appropriate function
		*/
		void AssignButtonTask(ButtonDescription& desc, cpptoml::table* button) {
			auto tasktoml = button->get_table("task");
			if (tasktoml) {
				auto task_name = tasktoml->get_as<std::string>("type");
				auto task_target = tasktoml->get_as<std::string>("target");
				auto target_name = tasktoml->get_as<std::string>("target_name");
				if (!task_name || !task_target || !target_name) {
					std::cout << "Invalid task description!" << std::endl;
					desc.hasTask = false;
				}
				else {
					auto it = tasks_map.find(*task_name);
					auto it2 = task_target_map.find(*task_target);
					if (it != tasks_map.end() && it2 != task_target_map.end()) {
						desc.task.task = it->second;
						desc.task.target_type = it2->second;
						desc.task.target_name = *target_name;
						desc.hasTask = true;
					}
					else
						desc.hasTask = false;
				}
			}
		}

		void CreateComponent(ComponentDescription* c, cpptoml::table* table) {
			c->name = table->get_as<std::string>("name").value_or("default");
			c->position = GetRectangle("position", table);
		}

		// Creation methods
		void CreateButtons(std::string mediaroot, WindowDescription & wd, cpptoml::table_array* buttontoml) {
			if (buttontoml) {
				for (const auto& button : *buttontoml) {
					SDL_Rect cliprect = GetRectangle("cliprect", button.get());
					std::string bgtexture = button->get_as<std::string>("bgtexture").value_or("");

					ButtonView bv(cliprect, mediaroot + bgtexture);
					ButtonDescription desc(bv);
					CreateComponent(&desc, button.get());
					AssignButtonTask(desc, button.get());
					wd.buttons.push_back(desc);
				}
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

		void PopulateGUIManager(GUIManager* guimanager, SAS_System::Renderer& renderer, std::vector<WindowDescription> descriptions, const CallbackMap& callbacks) 
		{
			// First add all the windows
			for (const auto& wd : descriptions) {
				auto window = std::make_unique<SAS_GUI::Window>(wd.position, &renderer, wd.name, wd.wv, wd.open);
				guimanager->AddWindow(std::move(window));
			}

			for (const auto& wd : descriptions) {
				auto window = guimanager->GetWindow(wd.name);
				for (const auto& b : wd.buttons) {
					auto cb = callbacks.find(b.name);
					if (cb != callbacks.end()) {
						window->AddComponent<SAS_GUI::Button>(b.position, b.bv, cb->second);
					}
					else if (b.hasTask) {
						if (b.task.target_type == TASK_TARGETS::WINDOW) {
							auto target = guimanager->GetWindow(b.task.target_name);
							if (target == nullptr) {
								std::cout << "Invalid Window name " << b.task.target_name << "associated with button " << b.name << std::endl;
								break;
							}
							if (b.task.task == BUTTON_TASKS::OPEN) {
								window->AddComponent<SAS_GUI::Button>(b.position, b.bv, 
									[target]() {
										target->OpenWindow();
									});
							}
							else if (b.task.task == BUTTON_TASKS::CLOSE) {
								window->AddComponent<SAS_GUI::Button>(b.position, b.bv, 
									[target]() {
										target->CloseWindow();
									});
							}
							else if (b.task.task == BUTTON_TASKS::TOGGLE) {
							}
							else if (b.task.task == BUTTON_TASKS::DISABLE) {
							}
							else if (b.task.task == BUTTON_TASKS::UNDISABLE) {
							}						
						}
					}
					else {
						std::cout << "Button " << b.name << " has not assigned functionality" << std::endl;
					}
				}
			}
		}

		void BuildGUIFromFile(GUIManager* guimanager, SAS_System::Renderer& renderer, std::string mediaroot, std::string file, const CallbackMap& callbacks) 
		{
			std::vector<WindowDescription> windowDescriptions;
			// First parse the gui file with cpptoml
			auto guitoml = cpptoml::parse_file(file);

			// Each gui file has an array of windows
			auto windows = guitoml->get_table_array("window");
			for (const auto& window : *windows) {
				windowDescriptions.push_back(CreateWindow(mediaroot, window.get()));			
			}
			
			PopulateGUIManager(guimanager, renderer, windowDescriptions, callbacks);
		}
	}
}