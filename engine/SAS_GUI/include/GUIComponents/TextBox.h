#pragma once
#include "ValueComponent.h"
#include "GUIViews/TextView.h"

namespace SAS_GUI {

	class TextBox : public ValueComponent<std::string>
	{
	public:

		TextBox(SDL_Rect position, const TextView& view) 
			: _value("")
			, _view(view)
			, _position(position)
			, focus_(false) 
			, cursortimer_(0)
			, showcursor_(true) 
			, cursorperiod_(500)
		{

		}

		~TextBox() {
		}

		void Update(const SDL_Rect& windowrect, const SAS_System::Input& input, bool& hasFocus, int elapsedtime);
		void Render(SAS_System::Renderer* renderer);

		std::string GetValue() { return _value; }

	private:
		std::string _value;
		TextView _view;
		SDL_Rect _position;

		bool focus_;
		int cursortimer_;
		bool showcursor_;
		const int cursorperiod_;

	};
}

