#include <iostream>
#include "GUIComponents\TextBox.h"
#include "GUIUtils.h"
#include "Model.h"

namespace SAS_GUI {
	void TextBox::Update(const SDL_Rect& windowrect, const SAS_System::Input& input, int elapsedtime) {
		int x;
		int y;
		input.getMouseState(x, y);

		// Check for intersection
		if (input.leftMousePressed()) {
			if (UTILS::isMouseOver(windowrect, _view.position, x, y)) {
				focus_ = true;
				SAS_System::StartTextInput(15, &_value);

				//Show the cursor immediately
				cursortimer_ = cursorperiod_;
			}
			else {
				if (focus_ == true)
					SAS_System::StopTextInput(&_value);

				focus_ = false;
				showcursor_ = false;
				cursortimer_ = 0;
			}
		}

		// Update Cursor
		if (focus_) {
			cursortimer_ += elapsedtime;

			if (cursortimer_ >= cursorperiod_) {
				cursortimer_ = 0;
				showcursor_ = !showcursor_;
			}
		}

	}

	// Relative to window or not??
	// Because im rendering to a texture, the position is already relative to the window                  
	void TextBox::Render(SAS_System::Renderer* renderer) {
		renderer->RenderOutlineRectangle(_view.position, SDL_Color{ 255,255,255,255 });
		renderer->RenderText(_value, _view.position.x, _view.position.y, _view.fontsize, _view.fontcolor, _view.fontpath);
	}
}