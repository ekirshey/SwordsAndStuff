#pragma once
#include <string>
#include <functional>
#include "Component.h"
#include "GUIViews/ButtonView.h"
#include "GUIDynamics/Dynamics.h"

namespace SAS_GUI {

#define DEFAULTDEBOUNCECOUNT 200
	class Model;

	class Button : public Component
	{
	public:

		Button(SDL_Rect position, const ButtonView& view);

		// rect in relation to container window
		Button(SDL_Rect position, const ButtonView& view, std::function<void()> func);
		Button(SDL_Rect position, const ButtonView& view, Dynamics dynamics, std::function<void()> func);

		// Unique_ptr so delete copy
		Button(const Button&) = delete;
		Button& operator=(const Button&) = delete;

		void Update(const SDL_Rect& windowrect, const SAS_System::Input& input, bool& hasFocus, int elapsedtime);
		void Render(SAS_System::Renderer* renderer);

		void NotifyObservers();
		void AddObserver(std::function<void()> observer);

	private:
		ButtonView _view;
		Dynamics _dynamics;
		SDL_Rect _position;
		std::function<void()> _callback;
		std::vector<std::function<void()>> _observers;

		int _debouncecounter;


	};
}