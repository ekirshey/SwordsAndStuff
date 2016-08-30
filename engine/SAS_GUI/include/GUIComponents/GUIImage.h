#pragma once

#include <vector>
#include "GUIComponent.h"

namespace SAS_GUI {
	/*
		Can be a single image or a vector of rectangles.
	*/
	class GUIImage : public GUIComponent
	{
	public:
		GUIImage(std::string imagepath, SDL_Point position, std::vector<SDL_Rect> cliprect) : imagepath_(imagepath), position_(position), cliprect_(cliprect), clipstate_(0) {
		}

		GUIImage(std::string imagepath, SDL_Point position, SDL_Rect cliprect) : imagepath_(imagepath), position_(position), clipstate_(0) {
			cliprect_.push_back(cliprect);
		}

		~GUIImage() {

		}

		void Render(const SDL_Rect& windowrect, SAS_Rendering::SDLManager* sdlmanager) {
			sdlmanager->RenderImage(imagepath_, position_.x + windowrect.x, position_.y + windowrect.y, &cliprect_[clipstate_]);
		}

		void NextClip() {
			if (++clipstate_ >= cliprect_.size())
				clipstate_ = 0;
		}

		void PreviousClip() {
			if (--clipstate_ < 0)
				clipstate_ = cliprect_.size() - 1;
		}

		void MoveToClip(int image) {
			if ((image > 0) && (image < cliprect_.size()))
				clipstate_ = image;
		}

	private:
		std::string imagepath_;
		SDL_Point position_;
		std::vector<SDL_Rect> cliprect_;
		int clipstate_;
	};
}
