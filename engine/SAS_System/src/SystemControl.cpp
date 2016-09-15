#include <iostream>
#include <SDL.h>
#include "SystemControl.h"
#include "Renderer.h"
#include "Input.h"

namespace SAS_System {

	void InitializeSystem() {
		// Initialize the base SDL. The Renderer will take care of the rest
		std::cout << "Initialize SAS System..." << std::endl;
		//Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			std::cout << "SDL could not initialize! SDL_Error: %s\n" << SDL_GetError() << std::endl;
			abort();
		}

	}

	void ShutdownSystem() {
		SDL_Quit();
	}

	void UpdateInput(Input* input) {
		input->clear();

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			// handle your event here
			switch (event.type) {
				case SDL_QUIT:
					/* Quit */
					input->setQuitState(true);
					break;
				case SDL_TEXTINPUT:
					/* Add new text onto the end of our text */
					break;

				case SDL_KEYDOWN:
					input->updateKeyState(event.key.keysym.scancode, Input::KeyState::PRESSED);
					break;
				case SDL_KEYUP:
					input->updateKeyState(event.key.keysym.scancode, Input::KeyState::RELEASED);
					break;
				case SDL_MOUSEBUTTONDOWN:
					input->updateMouseState(event.button.button, Input::KeyState::PRESSED);
					break;
				case SDL_MOUSEBUTTONUP:
					input->updateMouseState(event.button.button, Input::KeyState::RELEASED);
					break;
			}
		}

	}


	int CurrentTicks() {
		return SDL_GetTicks();
	}
}