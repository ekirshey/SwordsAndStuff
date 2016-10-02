#pragma once

#include <functional>
#include <cmath>
#include "Input/Input.h"
#include <iostream>
#include "SystemControl.h"
#include "GUIUtils.h"

namespace SAS_GUI {

	// Module Declerations
	class UpdateModule {
		public:
			virtual ~UpdateModule() {}
			// Overwrite for image type update
			virtual void update(const SDL_Rect& windowrect, SDL_Rect& position, SDL_Rect& cliprect) = 0;
	};

	class InputModule {
		public:
			virtual ~InputModule() {}
			virtual void handleInput(const SDL_Rect& windowrect, const SAS_System::Input& input, SDL_Rect& position, SDL_Rect& cliprect) = 0;
	};

	class VerticalBounceModule : public UpdateModule {
		public:
			VerticalBounceModule(int origin) 
				: _origin(origin)
				, _lasttickcount(0)
				, _direction(1)
			{

			}

			// Do some bounce
			void update(const SDL_Rect& windowrect, SDL_Rect& position, SDL_Rect& cliprect) {
				int currentticks = SAS_System::CurrentTicks();

				if (_lasttickcount == 0)
					_lasttickcount = currentticks;

				int vel = (currentticks - _lasttickcount) / 15;
				position.y += vel * _direction;
				if (std::abs(position.y - _origin) > 5) {
					_direction *= -1;
				}
				_lasttickcount = currentticks;
			}
		private:
			int _origin;
			int _lasttickcount;
			int _direction;

	};
	
	class HorizontalBounceModule : public UpdateModule {
		public:
			HorizontalBounceModule(int origin) 
				: _origin(origin)
				, _lasttickcount(0)
				, _direction(1)
			{

			}

			// Do some bounce
			void update(const SDL_Rect& windowrect, SDL_Rect& position, SDL_Rect& cliprect) {
				int currentticks = SAS_System::CurrentTicks();

				if (_lasttickcount == 0)
					_lasttickcount = currentticks;

				int vel = (currentticks - _lasttickcount) / 15;
				position.x += vel * _direction;
				if (std::abs(position.x - _origin) > 5) {
					_direction *= -1;
				}
				_lasttickcount = currentticks;
			}
		private:
			int _origin;
			int _lasttickcount;
			int _direction;

	};

	class HoverModule : public InputModule {
		public:
			HoverModule(const SDL_Rect& initialpos, const SDL_Rect& hoverpos) 
				: _initialpos(initialpos)
				, _hoverpos(hoverpos)
			{

			}

			void handleInput(const SDL_Rect& windowrect, const SAS_System::Input& input, 
				SDL_Rect& position, SDL_Rect& cliprect) 
			{
				int x;
				int y;
				input.getMouseState(x, y);

				if (UTILS::isMouseOver(windowrect, position, x, y))
					cliprect = _hoverpos;
				else
					cliprect = _initialpos;

			}
		private:
			SDL_Rect _initialpos;
			SDL_Rect _hoverpos;
	};

	using vec_pUpdate = std::vector<std::unique_ptr<UpdateModule> >;
	using vec_pInput = std::vector<std::unique_ptr<InputModule> >;

	class Dynamics {
		public:
			
			Dynamics(std::vector<std::unique_ptr<UpdateModule> > update, 
						  std::vector<std::unique_ptr<InputModule> > input) 
				: _updateModules(std::move(update))
				, _inputModules(std::move(input))
			{

			}

			void update(const SDL_Rect windowrect, SDL_Rect& position, SDL_Rect& cliprect) {
				for (auto& u : _updateModules) {
					u->update(windowrect, position, cliprect);
				}

			}

			void handleInput(const SDL_Rect windowrect, const SAS_System::Input& input, 
				SDL_Rect& position, SDL_Rect& cliprect) {
				for (auto& i : _inputModules) {
					i->handleInput(windowrect, input, position, cliprect);
				}
			}

		private:
			std::vector<std::unique_ptr<UpdateModule>> _updateModules;
			std::vector<std::unique_ptr<InputModule>> _inputModules;
	};

}

