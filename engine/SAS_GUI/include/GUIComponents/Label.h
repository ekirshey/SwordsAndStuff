#pragma once

#include "Component.h"
#include "GUIViews/TextView.h"
#include <iostream>

namespace SAS_GUI {
	class Label : public Component
	{
	public:
		Label(const TextView& view, std::string text)
			: _view(view)
			, _text(text)
		{
		}

		~Label() {

		}

		void Update(const SDL_Rect& windowrect, const SAS_System::Input& input, bool& hasFocus, int elapsedtime) {
		
		}

		void Render(SAS_System::Renderer* renderer) {
			renderer->RenderText(_text, _view.position.x, _view.position.y, 
				_view.fontsize, _view.fontcolor, _view.fontpath);
		}
		
	private:
		std::string _text;
		int _getstringkey;

		TextView _view;
	};

}
