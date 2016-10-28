#include "GUIWindow.h"
#include <iostream>
namespace SAS_GUI {
	GUIWindow::GUIWindow(SAS_System::Renderer* renderer, std::string windowname, const WindowView& view, bool open) 
		: windowname_(windowname)
		, view_(view)
		, open_(open)
	{
		guitexture_ = renderer->CreateTargetTexture(view_.position.w, view_.position.h);

		// Add the close button
	}

	GUIWindow::~GUIWindow()
	{
	}

	bool GUIWindow::Update(int elapsedtime, const SAS_System::Input& input) {
		bool hasFocus = false;
		bool tempFocus;
		if (IsOpen()) {
			for (auto i = 0; i < guicomponents_.size(); i++) {
				tempFocus = false;
				// Split up input and render handling for some hypothetical future where input in a window is disabled
				guicomponents_[i]->Update(view_.position, input, tempFocus, elapsedtime);
				hasFocus ^= tempFocus;
			}
		}
		return hasFocus;
	}

	void GUIWindow::Render(SAS_System::Renderer* renderer) {
		if (IsOpen()) {
			renderer->SetRenderTarget(guitexture_);
			// Render to target texture at the origin
			renderer->RenderImage(view_.texture, 0, 0);

			for (auto i = 0; i < guicomponents_.size(); i++) {
				guicomponents_[i]->Render(renderer);
			}

			renderer->DefaultRenderTarget();
			renderer->RenderTargetTexture(guitexture_, view_.position.x, view_.position.y);
		}
	}
}