#include "..\..\..\include\GUI\GUIComponents\GUIWindow.h"

GUIWindow::GUIWindow(SDLManager* sdlmanager, std::string windowname, SDL_Rect windowrect, 
	std::string focusedwindowtexture, std::string windowtexture, bool open) :
	sdlmanager_(sdlmanager), windowname_(windowname), windowrect_(windowrect),focusedwindowtexture_(focusedwindowtexture),
	windowtexture_(windowtexture), open_(open)
{
	guitexture_ = SDL_CreateTexture(sdlmanager_->GetRenderer(), SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, windowrect_.w, windowrect_.h);
	
}


GUIWindow::~GUIWindow()
{
}

void GUIWindow::Update(int elapsedtime) {
	if (IsOpen()) {
		SDL_SetRenderTarget(sdlmanager_->GetRenderer(), guitexture_);

		SDL_Rect cliprect = { 0,0,1280,640 };
		sdlmanager_->RenderImage(windowtexture_, windowrect_.x, windowrect_.y, &cliprect);

		for (int i = 0; i < guicomponents_.size(); i++) {
			// Split up input and render handling for some hypothetical future where input in a window is disabled
			guicomponents_[i]->HandleInput(windowrect_, sdlmanager_, elapsedtime);
			guicomponents_[i]->Render(windowrect_, sdlmanager_);
		}

		SDL_SetRenderTarget(sdlmanager_->GetRenderer(), NULL);

		SDL_RenderCopy(sdlmanager_->GetRenderer(), guitexture_, &windowrect_, NULL);
	}
}