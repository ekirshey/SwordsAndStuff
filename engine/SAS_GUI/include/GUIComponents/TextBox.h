#pragma once
#include "GUIComponent.h"

namespace SAS_GUI {
	class TextBox : public GUIComponent
	{
	public:
		TextBox(std::string* valueToChange, SDL_Rect rect, int fontsize, SDL_Color fontcolor, std::string fontpath) :
			value_(valueToChange), rect_(rect), storedString(""), fontsize_(fontsize), fontcolor_(fontcolor), fontpath_(fontpath),
			focus_(false), cursortimer_(0), showcursor_(true) {

		}

		~TextBox() {
		}

		void HandleInput(const SDL_Rect& windowrect, SAS_Rendering::SDLManager* sdlmanager, int elapsedtime);
		void Render(const SDL_Rect& windowrect, SAS_Rendering::SDLManager* sdlmanager);

	private:
		std::string* value_;
		SDL_Rect rect_;
		std::string storedString;

		// Font look
		int fontsize_;
		SDL_Color fontcolor_;
		std::string fontpath_;

		bool focus_;
		int cursortimer_;
		bool showcursor_;
		const int cursorperiod_ = 500;

	};
}

