#pragma once

#include "GUIComponent.h"
#include <iostream>

namespace SAS_GUI {
	class DynamicText : public GUIComponent
	{
	public:
		DynamicText(const std::string* text, SDL_Rect rect, int fontsize, SDL_Color fontcolor, std::string fontpath) :
			text_(text), rect_(rect), fontsize_(fontsize), fontcolor_(fontcolor), fontpath_(fontpath) {

		}

		~DynamicText() {

		}

		void Render(const SDL_Rect& windowrect, SAS_Rendering::SDLManager* sdlmanager) {
			sdlmanager->RenderText(*text_, rect_.x + windowrect.x, rect_.y + windowrect.y, fontsize_, fontcolor_, fontpath_);
		}

	private:
		const std::string* text_;
		SDL_Rect rect_;

		// Font look
		int fontsize_;
		SDL_Color fontcolor_;
		std::string fontpath_;
	};

}