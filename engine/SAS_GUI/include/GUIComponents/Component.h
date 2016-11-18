#pragma once
#include "Input/Input.h"
#include "Rendering/Renderer.h"


namespace SAS_GUI {
	class Component
	{

	public:
		virtual void Update(const SDL_Rect& windowrect, const SAS_System::Input& input, bool& hasFocus, int elapsedtime) = 0;
		virtual void Render(SAS_System::Renderer* renderer) = 0;

		virtual ~Component() {}
	};
}
