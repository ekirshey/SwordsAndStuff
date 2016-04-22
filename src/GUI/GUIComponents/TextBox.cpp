#include <iostream>
#include "..\..\..\include\GUI\GUIComponents\TextBox.h"

void TextBox::HandleInput(const SDL_Rect& windowrect, SDLManager* sdlmanager) {
	auto mousestate = sdlmanager->GetMouseState();
	int x;
	int y;
	SDL_GetMouseState(&x, &y);

	int relativeX = rect_.x + windowrect.x;
	int relativeY = rect_.y + windowrect.y;

	// Check for intersection
	if (mousestate[LEFT_PRESSED]) {
		if (((x > relativeX) && (x < (rect_.w + relativeX))) &&
			((y > relativeY) && (y < (rect_.h + relativeY)))) {
			focus_ = true;
			sdlmanager->RecordInput(15, &storedString);

			//Show the cursor immediately
			cursortimer_ = cursorperiod_;
		}
		else {
			if (focus_ == true)
				sdlmanager->StopInput(&storedString);
			focus_ = false;
			showcursor_ = false;
			cursortimer_ = 0;
		}
	}
}	

void TextBox::Render(const SDL_Rect& windowrect, SDLManager* sdlmanager, int elapsedtime) {

	sdlmanager->RenderFillRectangle(rect_, 255, 255, 255, 255);
	
	sdlmanager->RenderText(storedString, rect_.x + windowrect.x, rect_.y + windowrect.y, fontsize_, fontcolor_, fontpath_);
	
	*value_ = storedString;

	// Draw Cursor
	if (focus_) {
		cursortimer_ += elapsedtime;

		if (cursortimer_ >= cursorperiod_) {
			cursortimer_ = 0;
			showcursor_ = !showcursor_;
		}

		if (showcursor_) {
			sdlmanager->RenderLine(rect_.x + windowrect.x + sdlmanager->ActiveStringLength() + 2,
				rect_.y + windowrect.y + rect_.h - 2,
				rect_.x + windowrect.x + sdlmanager->ActiveStringLength() + 2,
				rect_.y + windowrect.y + 2,
				255, 0, 0, 255
				);
		}
	}
}