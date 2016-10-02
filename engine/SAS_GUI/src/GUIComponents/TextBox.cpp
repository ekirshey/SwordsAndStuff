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
				//input.startRecordingTextInput(15, &storedString);

				//Show the cursor immediately
				cursortimer_ = cursorperiod_;
			}
			else {
				if (focus_ == true)
					//input.stopRecordingTextInput(&storedString);
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

		*value_ = storedString;
	}

	void TextBox::Render(const SDL_Rect& windowrect, SAS_System::Renderer* renderer) {
#ifdef FOO

		sdlmanager->RenderFillRectangle(rect_, 255, 255, 255, 255);

		sdlmanager->RenderText(storedString, rect_.x + windowrect.x, rect_.y + windowrect.y, fontsize_, fontcolor_, fontpath_);

		if (showcursor_) {
			sdlmanager->RenderLine(rect_.x + windowrect.x + sdlmanager->ActiveStringLength() + 2,
				rect_.y + windowrect.y + rect_.h - 2,
				rect_.x + windowrect.x + sdlmanager->ActiveStringLength() + 2,
				rect_.y + windowrect.y + 2,
				255, 0, 0, 255
				);
		}
#endif
	}
}