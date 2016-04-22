#pragma once

#include "GUIComponent.h"

class GUIImage : public GUIComponent
{
	public:
		GUIImage(std::string imagepath, SDL_Rect rect) : imagepath_(imagepath), rect_(rect) {

		}

		~GUIImage() {

		}

		void Render(const SDL_Rect& windowrect, SDLManager* sdlmanager, int elapsedtime) {
			sdlmanager->RenderImage(imagepath_, rect_.x + windowrect.x, rect_.y + windowrect.y);
		}

	private:
		std::string imagepath_;
		SDL_Rect rect_;
};

