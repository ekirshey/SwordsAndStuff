#include <iostream>
#include "DropdownMenu.h"
#include "GUIUtils.h"

namespace SAS_GUI {
	DropdownMenu::DropdownMenu(const DropdownMenuView& dropdownview, const TextView& textview, std::vector<std::string> menuitems) 
		: _dropdownview(dropdownview)
		, _textview(textview)
		, _menuitems(menuitems)
		, _dropdownopen(false)
		, _selectedvalue(0)
	{

	}

	void DropdownMenu::Update(const SDL_Rect& windowrect, const SAS_System::Input& input, bool& hasFocus, int elapsedtime) {
		int x;
		int y;
		input.getMouseState(x, y);

		// Update the model based on input
		if (input.leftMouseReleased()) {
			if (UTILS::isMouseOver(windowrect, _dropdownview.menubox, x, y)) {
				std::cout << "clicked.." << std::endl;
				_dropdownopen = true;
			}
			else {
				_dropdownopen = false;
			}
		}

	}

	void DropdownMenu::Render(SAS_System::Renderer* renderer) {
		renderer->RenderFillRectangle(_dropdownview.menubox, SDL_Color{ 255,255,255,255 });
		if (_dropdownopen) {
			renderer->RenderFillRectangle(_dropdownview.dropdownbox, SDL_Color{ 255,0,255,255 });
		}
	}
}