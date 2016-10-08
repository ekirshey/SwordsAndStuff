#include <iostream>
#include <SDL.h>
#include "SystemControl.h"
#include "Renderer.h"
#include "Input.h"

namespace SAS_System {
	namespace {
		std::string* _startingstream = nullptr;
		int _streamlength = 0;

		std::string* _stoppingstream = nullptr;
	}
	
	void InitializeSystem() {
		// Initialize the base SDL. The Renderer will take care of the rest
		std::cout << "Initialize SAS System..." << std::endl;
		//Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			std::cout << "SDL could not initialize! SDL_Error: %s\n" << SDL_GetError() << std::endl;
			abort();
		}

		// Turn off text input initially (?)
		SDL_StopTextInput();

	}

	void ShutdownSystem() {
		SDL_Quit();
	}

	void UpdateInput(Input* input) {
		input->clear();

		if (_stoppingstream != nullptr)
			input->stopRecordingTextInput(_stoppingstream);

		if (_startingstream != nullptr)
			input->startRecordingTextInput(_streamlength, _startingstream);

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			// handle your event here
			switch (event.type) {
				case SDL_QUIT:
					/* Quit */
					input->setQuitState(true);
					break;
				case SDL_TEXTINPUT:
					/* Add new character onto the end of our text */
					input->updateTextInput(event.text.text);
					break;
				case SDL_KEYDOWN:
					input->updateKeyState(event.key.keysym.scancode, Input::KeyState::PRESSED);
					if (event.key.keysym.sym == SDLK_BACKSPACE) {
						input->handleBackspace();
					}
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
				default:
					break;
			}
		}

		// Set Mousestate
		int x, y;
		SDL_GetMouseState(&x, &y);
		input->setMouseState(x, y);

	}


	int CurrentTicks() {
		return SDL_GetTicks();
	}
	
	void StartTextInput(int streamlength, std::string* stream) {
		SDL_StartTextInput();
		_startingstream = stream;
		_streamlength = streamlength;
		_stoppingstream = nullptr;
	}

	void StopTextInput(std::string* stream) {
		_stoppingstream = stream;
		if (_stoppingstream == _startingstream) {
			SDL_StopTextInput();
			_startingstream = nullptr;
		}
	}
}