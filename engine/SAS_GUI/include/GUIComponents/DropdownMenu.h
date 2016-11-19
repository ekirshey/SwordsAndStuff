#pragma once

#include <vector>
#include "ValueComponent.h"
#include "GUIViews/DropdownMenuView.h"
#include "GUIViews/TextView.h"

namespace SAS_GUI {

	class DropdownMenu : public ValueComponent<std::string> {
		public:
			DropdownMenu(SAS_System::Renderer& renderer, SDL_Rect position, const DropdownMenuView& dropdownview, std::vector<std::string> menuitems);

			void Update(const SDL_Rect& windowrect, const SAS_System::Input& input, bool& hasFocus, int elapsedtime);
			void Render(SAS_System::Renderer* renderer);

			std::string GetValue() { return _menuitems[_selectedvalue]; }
		private:	
			SDL_Rect _position;
			DropdownMenuView _dropdownview;
			std::vector<std::string> _menuitems;
			int _dropdowntextureid;

			// Logic variables
			bool _dropdownopen;
			int _selectedvalue;
			int _hoveredvalue;
			bool _hovered;
			SDL_Rect _menuposition;
	};
}
