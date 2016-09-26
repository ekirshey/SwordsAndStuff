#include "GUIWindow.h"

namespace SAS_GUI {
	GUIWindow::GUIWindow( SAS_System::Renderer* renderer, std::string windowname, SDL_Rect windowrect,
		std::string focusedwindowtexture, std::string windowtexture, bool open) 
		: windowname_(windowname)
		, windowrect_(windowrect)
		, focusedwindowtexture_(focusedwindowtexture)
		, windowtexture_(windowtexture)
		, open_(open)
	{
		guitexture_ = renderer->CreateTargetTexture(windowrect_.w, windowrect_.h);
	}


	GUIWindow::~GUIWindow()
	{
	}



	void GUIWindow::Update(int elapsedtime, const SAS_System::Input& input) {
		if (IsOpen()) {
			for (int i = 0; i < guicomponents_.size(); i++) {
				// Split up input and render handling for some hypothetical future where input in a window is disabled
				guicomponents_[i]->HandleInput(windowrect_, input, elapsedtime);
			}
		}
	}

	void GUIWindow::Render(SAS_System::Renderer* renderer) {

		renderer->RenderToTargetTexture(windowtexture_, guitexture_, windowrect_.x, windowrect_.y);

		for (int i = 0; i < guicomponents_.size(); i++) {
			guicomponents_[i]->Render(windowrect_, renderer, guitexture_);
		}

		renderer->RenderTargetTexture(guitexture_, windowrect_.x, windowrect_.y);
	}
}