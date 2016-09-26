#pragma once
#include "Input/Input.h"
#include "Rendering/Renderer.h"


namespace SAS_GUI {
	class GUIComponent
	{

	public:
		virtual void HandleInput(const SDL_Rect& windowrect, const SAS_System::Input& input, int elapsedtime) {}
		virtual void Render(const SDL_Rect& windowrect, SAS_System::Renderer* renderer, int targettexture) = 0;

		virtual ~GUIComponent() {}
	};
}
