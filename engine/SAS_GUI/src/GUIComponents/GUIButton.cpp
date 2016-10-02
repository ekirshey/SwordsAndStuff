#include "GUIButton.h"
#include "Model.h"
#include "GUIUtils.h"

namespace SAS_GUI {

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

		void GUIButton::Update(const SDL_Rect& windowrect, const SAS_System::Input& input, int elapsedtime) {
			int x;
			int y;
			input.getMouseState(x, y);

			SAS_System::geti();
			_debouncecounter += elapsedtime;

			// Model independent update and input handling
			_dynamics.update(windowrect, _view.position, _view.cliprect);
			_dynamics.handleInput(windowrect, input, _view.position, _view.cliprect);

			// Update the model based on input
			if (input.leftMouseReleased()) { 
				if (UTILS::isMouseOver(windowrect, _view.position, x, y)) {
					if (_debouncecounter >= DEFAULTDEBOUNCECOUNT) {
						_model->callFunction(_clickedkey);
						NotifyObservers();
						_debouncecounter = 0;
					}
				}
			}
		}

		void GUIButton::Render(const SDL_Rect& windowrect, SAS_System::Renderer* renderer) {
			renderer->RenderImage(_view.texture, _view.position.x + windowrect.x, 
				_view.position.y + windowrect.y, &_view.cliprect);
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