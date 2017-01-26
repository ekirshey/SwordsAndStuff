#pragma once

#include <string>
#include <unordered_map>
#include "GUIManager.h"
#include "GUIViews/ButtonView.h"
#include "GUIViews/DropdownMenuView.h"
#include "GUIViews/TextView.h"

namespace SAS_GUI {
	namespace GUIBuilder {
		using CallbackMap = std::unordered_map< std::string, std::function<void()> >;
		enum BUTTON_TASKS {OPEN, CLOSE, TOGGLE, DISABLE, UNDISABLE};
		enum TASK_TARGETS {WINDOW, BUTTON};

		struct ComponentDescription {
			std::string name;
			SDL_Rect position;
		};

		struct ButtonTask {
			BUTTON_TASKS task;
			TASK_TARGETS target_type;
			std::string target_name;
		};

		struct ButtonDescription : public ComponentDescription {
			ButtonView bv;
			ButtonTask task;
			bool hasTask;

			ButtonDescription(ButtonView b)
				: bv(b)
			{

			}
		};

		struct DropdownMenuViewDescription : public ComponentDescription {
			DropdownMenuView bv;
		};

		struct TextInputDescription : public ComponentDescription {
			TextView bv;
		};

		struct WindowDescription : public ComponentDescription {
			WindowView wv;
			bool open;
			std::vector<ButtonDescription> buttons;
			std::vector<DropdownMenuViewDescription> dropdownmenus;
			std::vector<TextInputDescription> textinputs;

			WindowDescription(WindowView w)
				: wv(w)
				, open(false)
			{

			}
		};

		std::vector<WindowDescription> BuildGUIFromFile(GUIManager* guimanager, SAS_System::Renderer& renderer, std::string mediaroot, std::string file, const CallbackMap& callbacks);

	}
}