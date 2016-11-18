#pragma once

namespace SAS_GUI {
	struct DropdownMenuView {
		SDL_Rect menubox;
		SDL_Rect dropdownbox;

		DropdownMenuView(SDL_Rect mb, SDL_Rect ddb) 
			: menubox(mb)
			, dropdownbox(ddb)
		{

		}
		
	};
}
