#pragma once

namespace SAS_GUI {
	struct TextView {
		int fontsize;
		SDL_Color fontcolor;
		std::string fontpath;

		TextView(int fontsize, SDL_Color fontcolor, std::string fontpath) 
			: fontsize(fontsize)
			, fontcolor(fontcolor)
			, fontpath(fontpath)
		{

		}
	};
}