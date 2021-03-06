#include "Button.h"
#include "Model.h"
#include "GUIUtils.h"

namespace SAS_GUI {
		
		Button::Button(SDL_Rect position, const ButtonView& view) 
			: _view(view)
			, _dynamics(Dynamics())
			, _position(position)
			, _debouncecounter(0)
		{

		}

		// rect in relation to container window
		Button::Button(SDL_Rect position, const ButtonView& view, std::function<void()> func) 
			: _view(view)
			, _position(position)
			, _callback(func)
			, _debouncecounter(0)
		{

		}

		// rect in relation to container window
		Button::Button(SDL_Rect position, const ButtonView& view, Dynamics dynamics, std::function<void()> func) 
			: _view(view)
			, _dynamics(std::move(dynamics))
			, _position(position)
			, _callback(func)
			, _debouncecounter(0)
		{

		}

		

		void Button::Update(const SDL_Rect& windowrect, const SAS_System::Input& input, bool& hasFocus, int elapsedtime) {
			int x;
			int y;
			input.getMouseState(x, y);

			// Do i need the debounce counter?
			_debouncecounter += elapsedtime;

			// Model independent update and input handling
			_dynamics.update(windowrect, _position, _view.cliprect);
			_dynamics.handleInput(windowrect, input, _position, _view.cliprect);

			// Update the model based on input
			if (input.leftMouseReleased()) { 
				if (UTILS::isMouseOver(windowrect, _position, x, y)) {
					//if (_debouncecounter >= DEFAULTDEBOUNCECOUNT) {
						_callback();
						NotifyObservers();
						_debouncecounter = 0;
					//}
				}
			}
		}

		void Button::Render( SAS_System::Renderer* renderer) {
			renderer->RenderImage(_view.texture, _position.x, 
				_position.y, &_view.cliprect);
		}

		void Button::NotifyObservers() {
			for (auto& f : _observers) {
				f();
			}
		}

		void Button::AddObserver(std::function<void()> observer) {
			_observers.push_back(observer);
		}
}