#pragma once
#include "Input/Input.h"
#include "Rendering/Renderer.h"


namespace SAS_GUI {
	class GUIComponent
	{

	public:
		virtual void Update(const SDL_Rect& windowrect, const SAS_System::Input& input, int elapsedtime) {}
		virtual void Render(SAS_System::Renderer* renderer) = 0;

		virtual ~GUIComponent() {}
	};
}
