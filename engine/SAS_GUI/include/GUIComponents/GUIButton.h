#pragma once
#include <string>
#include <functional>
#include "GUIComponent.h"
#include "GUIViews/ButtonView.h"
#include "GUIDynamics/Dynamics.h"

namespace SAS_GUI {

#define DEFAULTDEBOUNCECOUNT 200
	class Model;

	class GUIButton : public GUIComponent
	{
	public:
		// rect in relation to container window
		GUIButton(const ButtonView& view, std::unique_ptr<Model> model, int clickedkey, 
			Dynamics dynamics);

		// Unique_ptr so delete copy
		GUIButton(const GUIButton&) = delete;
		GUIButton& operator=(const GUIButton&) = delete;

		void Update(const SDL_Rect& windowrect, const SAS_System::Input& input, int elapsedtime);
		void Render(const SDL_Rect& windowrect, SAS_System::Renderer* renderer);

		void NotifyObservers();
		void AddObserver(std::function<void()> observer);

	private:
		ButtonView _view;
		std::unique_ptr<Model> _model;
		Dynamics _dynamics;

		std::vector<std::function<void()>> _observers;

		// Keys for grabbing data from the model
		int _clickedkey;

		int _debouncecounter;


	};
}