#pragma once

namespace SAS_GUI {
	struct WindowView {
		SDL_Rect cliprect;
		std::string texture;

		WindowView(SDL_Rect cr, std::string t) 
			: cliprect(cr)
			, texture(t)
		{
		}
	};
}
