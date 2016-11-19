#pragma once

#include "Component.h"
#include "GUIViews/TextView.h"
#include <iostream>

namespace SAS_GUI {
	template<typename T>
	class DynamicText : public Component
	{
	public:
		DynamicText(SDL_Rect position, const TextView& view, const T& data) 
			: _view(view)
			, _position(position)
			, _data(data)
			, _currentdata(data)
			, _text(std::to_string(data))
		{
		}

		~DynamicText() {

		}

		void Update(const SDL_Rect& windowrect, const SAS_System::Input& input, bool& hasFocus, int elapsedtime) {
			if (_data != _currentdata) {
				_currentdata = _data;
				_text = std::to_string(_currentdata);
			}
		}

		void Render(SAS_System::Renderer* renderer) {
			renderer->RenderText(_text, _position.x, _position.y, 
				_view.fontsize, _view.fontcolor, _view.fontpath);
		}
		
	private:
		TextView _view;
		SDL_Rect _position;
		const T& _data;
		T _currentdata;
		std::string _text;
	};

}