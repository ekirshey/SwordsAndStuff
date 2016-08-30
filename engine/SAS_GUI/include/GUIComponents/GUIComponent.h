#pragma once
#include "SDLManager.h"

namespace SAS_GUI {
	class GUIComponent
	{

	public:
		virtual void HandleInput(const SDL_Rect& windowrect, SAS_Rendering::SDLManager* sdlmanager, int elapsedtime) {}
		virtual void Render(const SDL_Rect& windowrect, SAS_Rendering::SDLManager* sdlmanager) = 0;

		virtual ~GUIComponent() {}
	};
}
