#include "GUIWindow.h"

namespace SAS_GUI {
	GUIWindow::GUIWindow( SAS_System::Renderer* renderer, std::string windowname, SDL_Rect windowrect,
		std::string focusedwindowtexture, std::string windowtexture, bool open) 
		: windowname_(windowname)
		, windowrect_(windowrect)
		, tabindex_(0)
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
			for (auto i = 0; i < guicomponents_.size(); i++) {
				// Split up input and render handling for some hypothetical future where input in a window is disabled
				guicomponents_[i]->Update(windowrect_, input, elapsedtime);
			}
		}
	}

	void GUIWindow::Render(SAS_System::Renderer* renderer) {

		renderer->SetRenderTarget(guitexture_);
		renderer->RenderImage(windowtexture_, windowrect_.x, windowrect_.y);

		for (auto i = 0; i < guicomponents_.size(); i++) {
			guicomponents_[i]->Render(windowrect_, renderer);
		}

		renderer->DefaultRenderTarget();
		renderer->RenderTargetTexture(guitexture_, windowrect_.x, windowrect_.y);
	}
}