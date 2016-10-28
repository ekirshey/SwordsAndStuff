#pragma once
#include "GUIComponent.h"
#include "GUIViews/TextView.h"

namespace SAS_GUI {

	class Model;
	
	class TextBox : public GUIComponent
	{
	public:
		TextBox(const TextView& view) 
			: _value("")
			, _view(view)
			, focus_(false) 
			, cursortimer_(0)
			, showcursor_(true) 
		{

		}

		~TextBox() {
		}

		void Update(const SDL_Rect& windowrect, const SAS_System::Input& input, bool& hasFocus, int elapsedtime);
		void Render(SAS_System::Renderer* renderer);

	private:
		std::string _value;
		std::unique_ptr<Model> _model;

		TextView _view;

		bool focus_;
		int cursortimer_;
		bool showcursor_;
		const int cursorperiod_ = 500;

	};
}

