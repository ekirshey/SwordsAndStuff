#include "GUIButton.h"
#include "Model.h"
#include "GUIUtils.h"

namespace SAS_GUI {
		
		GUIButton::GUIButton(const ButtonView& view) 
			: _view(view)
			, _model(nullptr)
			, _dynamics(Dynamics())
			, _debouncecounter(0)
		{

		}

		// rect in relation to container window
		GUIButton::GUIButton(const ButtonView& view, std::unique_ptr<Model> model, int clickedkey,
			Dynamics dynamics) 
			: _view(view)
			, _model(std::move(model))
			, _clickedkey(clickedkey)
			, _dynamics(std::move(dynamics))
			, _debouncecounter(0)
		{

		}

		

		void GUIButton::Update(const SDL_Rect& windowrect, const SAS_System::Input& input, bool& hasFocus, int elapsedtime) {
			int x;
			int y;
			input.getMouseState(x, y);

			_debouncecounter += elapsedtime;

			// Model independent update and input handling
			_dynamics.update(windowrect, _view.position, _view.cliprect);
			_dynamics.handleInput(windowrect, input, _view.position, _view.cliprect);

			// Update the model based on input
			if (input.leftMouseReleased()) { 
				if (UTILS::isMouseOver(windowrect, _view.position, x, y)) {
					if (_debouncecounter >= DEFAULTDEBOUNCECOUNT) {
						// Not all buttons have a model
						if (_model != nullptr)
							_model->callFunction(_clickedkey);
						NotifyObservers();
						_debouncecounter = 0;
					}
				}
			}
		}

		void GUIButton::Render( SAS_System::Renderer* renderer) {
			renderer->RenderImage(_view.texture, _view.position.x, 
				_view.position.y, &_view.cliprect);
		}

		void GUIButton::NotifyObservers() {
			for (auto& f : _observers) {
				f();
			}
		}

		void GUIButton::AddObserver(std::function<void()> observer) {
			_observers.push_back(observer);
		}
}