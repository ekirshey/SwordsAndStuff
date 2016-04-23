#pragma once
#include <string>
#include "GUIComponent.h"
#include "../../SDL/SDLManager.h"

#define DEFAULTDEBOUNCECOUNT 200

template<typename T>
class GUIButton : public GUIComponent
{
public:
	// rect in relation to container window
	GUIButton(SDL_Rect rect, SDL_Rect cliprect, std::string texture, const T& func) :
		rect_(rect), cliprect_(cliprect), texture_(texture), function_(func), clicked_(false), workingClipRect_(cliprect), debouncelength_(DEFAULTDEBOUNCECOUNT), debouncecounter_(0)
	{

	}

	GUIButton(SDL_Rect rect, SDL_Rect cliprect, std::string texture, const T& func, int debouncecounter) :
		rect_(rect), cliprect_(cliprect), texture_(texture), function_(func), clicked_(false), workingClipRect_(cliprect), debouncelength_(debouncecounter), debouncecounter_(0)
	{

	}


	~GUIButton() {}

	void HandleInput(const SDL_Rect& windowrect, SDLManager* sdlmanager, int elapsedtime) {

		auto mousestate = sdlmanager->GetMouseState();
		int x;
		int y;
		SDL_GetMouseState(&x, &y);

		int relativeX = rect_.x + windowrect.x;
		int relativeY = rect_.y + windowrect.y;

		debouncecounter_ += elapsedtime;

		// Check for intersection
		if (((x > relativeX) && (x < (rect_.w + relativeX))) &&
			((y > relativeY) && (y < (rect_.h + relativeY)))) {
			workingClipRect_.y += workingClipRect_.h;
			if (mousestate[LEFT_PRESSED] || (mousestate[LEFT_MOUSEBUTTON_HELD] && clicked_)) {
				workingClipRect_.y += workingClipRect_.h;
				clicked_ = true;
				if (debouncecounter_ >= debouncelength_) {
					function_();
					debouncecounter_ = 0;
				}
			}
			else
				clicked_ = false;
		}
	}

	void Render(const SDL_Rect& windowrect, SDLManager* sdlmanager) {

		sdlmanager->RenderImage(texture_, rect_.x + windowrect.x, rect_.y + windowrect.y, &workingClipRect_);

		// Reset the workingClipRect_ to the baseline
		workingClipRect_ = cliprect_;
	}

private:
	const SDL_Rect rect_;
	const SDL_Rect cliprect_;
	bool clicked_;

	std::string texture_;

	T function_;
	SDL_Rect workingClipRect_;

	int debouncelength_;
	int debouncecounter_;

};