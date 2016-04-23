#pragma once
#include "../../SDL/SDLManager.h"

class GUIComponent
{

public:
	virtual void HandleInput(const SDL_Rect& windowrect, SDLManager* sdlmanager, int elapsedtime) {}
	virtual void Render(const SDL_Rect& windowrect, SDLManager* sdlmanager) = 0;

	virtual ~GUIComponent() {}
};

