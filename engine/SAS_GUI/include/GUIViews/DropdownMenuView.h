#pragma once
#include "ButtonView.h"
#include "TextView.h"

namespace SAS_GUI {
	struct DropdownMenuView {
		int maxwidth;
		int maxheight;
		SDL_Color menucolor;
		SDL_Color dropdowncolor;
		SDL_Color highlightcolor;
		ButtonView buttonview;
		TextView textview;

		DropdownMenuView(int mw, int mh, SDL_Color mc, SDL_Color dpc, SDL_Color hlc, ButtonView b, TextView tv) 
			: maxwidth(mw)
			, maxheight(mh)
			, menucolor(mc)
			, dropdowncolor(dpc)
			, highlightcolor(hlc)
			, buttonview(b)
			, textview(tv)
		{

		}
		
	};
}
