#pragma once

#include "GUIComponent.h"
#include "GUIViews/TextView.h"
#include "Model.h"
#include <iostream>

namespace SAS_GUI {
	class DynamicText : public GUIComponent
	{
	public:
		DynamicText(const TextView& view, std::unique_ptr<Model> model, int getstringkey)
			: _view(view)
			, _model(std::move(model))
			, _getstringkey(getstringkey)
		{
		}

		~DynamicText() {

		}
		void Update(const SDL_Rect& windowrect, const SAS_System::Input& input, int elapsedtime) {
			_text = _model->getValue(_getstringkey);
		}

		void Render(const SDL_Rect& windowrect, SAS_System::Renderer* renderer) {
			renderer->RenderText(_text, _view.position.x + windowrect.x, _view.position.y + windowrect.y, 
				_view.fontsize, _view.fontcolor, _view.fontpath);
		}
		
	private:
		std::string _text;
		std::unique_ptr<Model> _model;
		int _getstringkey;

		TextView _view;
	};

}