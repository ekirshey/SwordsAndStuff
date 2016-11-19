#pragma once

namespace SAS_GUI {
	struct ButtonView {
		SDL_Rect cliprect;
		std::string texture;

		ButtonView(SDL_Rect cr, std::string t) 
			: cliprect(cr)
			, texture(t)
		{
		}
	};
}