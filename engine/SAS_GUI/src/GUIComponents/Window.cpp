#include "Window.h"
#include <iostream>
namespace SAS_GUI {
	Window::Window(SAS_System::Renderer* renderer, std::string windowname, const WindowView& view, bool open) 
		: _windowname(windowname)
		, _view(view)
		, _open(open)
	{
		_guitexture = renderer->CreateTargetTexture(_view.position.w, _view.position.h);

		// Add the close button
	}

	Window::~Window()
	{
	}

	bool Window::Update(int elapsedtime, const SAS_System::Input& input) {
		bool hasFocus = false;
		bool tempFocus;
		if (IsOpen()) {
			for (auto i = 0; i < _guicomponents.size(); i++) {
				tempFocus = false;
				// Split up input and render handling for some hypothetical future where input in a window is disabled
				_guicomponents[i]->Update(_view.position, input, tempFocus, elapsedtime);
				hasFocus ^= tempFocus;
			}
		}
		return hasFocus;
	}

	void Window::Render(SAS_System::Renderer* renderer) {
		if (IsOpen()) {
			renderer->SetRenderTarget(_guitexture);
			// Render to target texture at the origin
			renderer->RenderImage(_view.texture, 0, 0);

			for (auto i = 0; i < _guicomponents.size(); i++) {
				_guicomponents[i]->Render(renderer);
			}

			renderer->DefaultRenderTarget();
			renderer->RenderTargetTexture(_guitexture, _view.position.x, _view.position.y);
		}
	}
}