#include "Window.h"
#include <iostream>

namespace SAS_GUI {
	Window::Window(SDL_Rect position, SAS_System::Renderer* renderer, std::string windowname, const WindowView& view, bool open) 
		: _position(position)
		, _windowname(windowname)
		, _view(view)
		, _open(open)
	{
		_guitexture = renderer->CreateTargetTexture(_position.w, _position.h);

		// Add the close button
	}

	Window::~Window()
	{
	}

	bool Window::Update(int elapsedtime, const SAS_System::Input& input, std::vector<Message> receiveQueue, int queuesize) {
		bool hasFocus = false;
		bool tempFocus;
		for (auto i = 0; i < _guicomponents.size(); i++) {
			tempFocus = false;
			// Always receive messages but only update if the window is open
			_guicomponents[i]->ReceiveMessages(receiveQueue, queuesize);
			if (IsOpen()) {
				_guicomponents[i]->Update(_position, input, tempFocus, elapsedtime);
				_guicomponents[i]->SendExternalMessage(_externalGUIQueue);
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
			renderer->RenderTargetTexture(_guitexture, _position.x, _position.y);
		}
	}

	void Window::_registerCursor(Cursor* cursor) {
		_cursor = cursor;
		for (auto& c : _guicomponents) {
			c->RegisterCursor(_cursor);
		}
	}
}