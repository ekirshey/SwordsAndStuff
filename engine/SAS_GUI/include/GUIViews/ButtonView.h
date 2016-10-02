#pragma once

namespace SAS_GUI {
	struct ButtonView {
		SDL_Rect position;
		SDL_Rect cliprect;
		std::string texture;

		ButtonView(SDL_Rect r, SDL_Rect cr, std::string t) 
		: position(r)
		, cliprect(cr)
		, texture(t)
		{
		}
	};
}