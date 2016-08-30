#pragma once
#include <string>
#include "GUIComponent.h"
#include "SDLManager.h"

namespace SAS_GUI {

#define DEFAULTDEBOUNCECOUNT 200


	class ButtonFunction {
	public:
		ButtonFunction() {}

		virtual void operator()() = 0;
	};

	class GUIButton : public GUIComponent
	{
	public:
		// rect in relation to container window
		GUIButton(SDL_Rect rect, SDL_Rect cliprect, std::string texture, std::unique_ptr<ButtonFunction> func) :
			rect_(rect), cliprect_(cliprect), texture_(texture), function_(std::move(func)), clicked_(false), workingClipRect_(cliprect), debouncelength_(DEFAULTDEBOUNCECOUNT), debouncecounter_(0)
		{

		}
		/*
			// Templated arguments in order to avoid an unnecessary copy
			template<typename... Args>
			GUIButton(SDL_Rect rect, SDL_Rect cliprect, std::string texture, Args&&... args) :
				rect_(rect), cliprect_(cliprect), texture_(texture), function_(std::forward<Args>(args)...), clicked_(false), workingClipRect_(cliprect), debouncelength_(DEFAULTDEBOUNCECOUNT), debouncecounter_(0)
			{

			}

			GUIButton(SDL_Rect rect, SDL_Rect cliprect, std::string texture, const T& func, int debouncecounter) :
				rect_(rect), cliprect_(cliprect), texture_(texture), function_(func), clicked_(false), workingClipRect_(cliprect), debouncelength_(debouncecounter), debouncecounter_(0)
			{

			}
		*/

		~GUIButton() {}

		void HandleInput(const SDL_Rect& windowrect, SAS_Rendering::SDLManager* sdlmanager, int elapsedtime) {

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
				if (mousestate[SAS_Rendering::LEFT_PRESSED] || (mousestate[SAS_Rendering::LEFT_MOUSEBUTTON_HELD] && clicked_)) {
					workingClipRect_.y += workingClipRect_.h;
					clicked_ = true;
					if (debouncecounter_ >= debouncelength_) {
						(*function_)();
						debouncecounter_ = 0;
					}
				}
				else
					clicked_ = false;
			}
		}

		void Render(const SDL_Rect& windowrect, SAS_Rendering::SDLManager* sdlmanager) {

			sdlmanager->RenderImage(texture_, rect_.x + windowrect.x, rect_.y + windowrect.y, &workingClipRect_);

			// Reset the workingClipRect_ to the baseline
			workingClipRect_ = cliprect_;
		}

	private:
		const SDL_Rect rect_;
		const SDL_Rect cliprect_;
		bool clicked_;

		std::string texture_;

		//T function_;
		std::unique_ptr<ButtonFunction> function_;
		SDL_Rect workingClipRect_;

		int debouncelength_;
		int debouncecounter_;

	};
}