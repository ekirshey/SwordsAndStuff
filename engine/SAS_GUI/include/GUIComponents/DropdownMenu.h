#pragma once

#include <vector>
#include "ValueComponent.h"
#include "GUIViews/DropdownMenuView.h"
#include "GUIViews/TextView.h"

namespace SAS_GUI {

	class DropdownMenu : public ValueComponent<std::string> {
		public:
			DropdownMenu(const DropdownMenuView& dropdownview, const TextView& textview, std::vector<std::string> menuitems);

			void Update(const SDL_Rect& windowrect, const SAS_System::Input& input, bool& hasFocus, int elapsedtime);
			void Render(SAS_System::Renderer* renderer);

			std::string GetValue() { return _menuitems[_selectedvalue]; }
		private:	
			DropdownMenuView _dropdownview;
			TextView _textview;
			std::vector<std::string> _menuitems;

			// Logic variables
			bool _dropdownopen;
			int _selectedvalue;
	};
}
