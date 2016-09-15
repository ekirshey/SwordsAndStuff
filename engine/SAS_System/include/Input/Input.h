#pragma once
#include "SystemDefines.h"
#include <vector>
#include <memory>

namespace SAS_System {

	class Input
	{
		public:
			enum KeyState {PRESSED, RELEASED, STILL};

		    DECLSPEC Input() : _quit(false) {
				_toupdate = std::make_unique<std::vector<Input::KeyState*>>();
			}

			DECLSPEC ~Input() {
			}

			bool DECLSPEC isKeyPressed(int key) {
				return _activekeys[key] == KeyState::PRESSED;
			}

			bool DECLSPEC isKeyReleased(int key) {
				return _activekeys[key] == KeyState::RELEASED;
			}

			bool DECLSPEC leftMousePressed() {
				return _activekeys[MouseButtons::LEFT] == KeyState::PRESSED;
			}

			bool DECLSPEC leftMouseReleased() {
				return _activekeys[MouseButtons::LEFT] == KeyState::RELEASED;
			}

			bool DECLSPEC Quit() {
				return _quit;
			}

			void updateKeyState(int key, KeyState state) {
				_activekeys[key] = state;
				_toupdate->push_back(&_activekeys[key]);
			}

			void updateMouseState(uint8_t button, KeyState state) {
				switch (button) {
					case SDL_BUTTON_LEFT:
						updateKeyState(Input::MouseButtons::LEFT, state);
						break;
					case SDL_BUTTON_RIGHT:
						updateKeyState(Input::MouseButtons::RIGHT, state);
						break;
				}
			}

			void clear() {
				for (uint32_t i = 0; i < _toupdate->size(); i++) {
					*_toupdate->at(i) = KeyState::STILL;
					_toupdate->pop_back();
				}
			}

			void setQuitState(bool quit) {
				_quit = quit;
			}

		private:
			bool _quit;
			// Numbers chosen above the max 512 button defined in SDL
			enum MouseButtons {LEFT = 800, RIGHT = 801, MIDDLE = 802};
			std::unique_ptr<std::vector<Input::KeyState*>> _toupdate; // pointer to do warnings about exposing std in a dll. different platforms have different implementations
			KeyState _activekeys[1000]; // At least all the SDL_SCANCODES and room for possibly more?
	};

}