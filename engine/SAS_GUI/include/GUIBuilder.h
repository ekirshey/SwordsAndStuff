#pragma once

#include <string>
#include "GUIManager.h"
#include "GUIViews/ButtonView.h"
#include "GUIViews/DropdownMenuView.h"
#include "GUIViews/TextView.h"

namespace SAS_GUI {
	namespace GUIBuilder {

		struct ComponentDescription {
			std::string name;
			SDL_Rect position;
		};

		struct ButtonDescription : public ComponentDescription {
			ButtonView bv;

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

		std::vector<WindowDescription> BuildGUIFromFile(GUIManager* guimanager, std::string mediaroot, std::string file);

	}
}