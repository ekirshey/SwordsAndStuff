#pragma once

namespace SAS_GUI {
	struct TextView {
		int fontsize;
		SDL_Color fontcolor;
		std::string fontpath;
		SDL_Rect position;

		TextView(int fontsize, SDL_Color fontcolor, std::string fontpath, SDL_Rect position) 
			: fontsize(fontsize)
			, fontcolor(fontcolor)
			, fontpath(fontpath)
			, position(position)
		{

		}
	};
}