#pragma once
#include "SystemDefines.h"
#include <vector>
#include <memory>
#include <string>

namespace SAS_System {
	#define MAXKEYS 1000
	class Input
	{
		public:
			struct RecordStream {
				std::string* stream;
				std::size_t maxcharacters;
				bool AtMaxLength() { return (stream->size() < maxcharacters); }

				RecordStream(std::string* s, size_t maxchars) : stream(s), maxcharacters(maxchars) {}
			};

			enum KeyState {PRESSED, RELEASED, STILL};

			DECLSPEC Input();
			DECLSPEC ~Input();			
			
			bool DECLSPEC isKeyPressed(int key) const;
			bool DECLSPEC isKeyReleased(int key) const;
			bool DECLSPEC leftMousePressed() const;
			bool DECLSPEC leftMouseReleased() const;
			bool DECLSPEC rightMousePressed() const;
			bool DECLSPEC rightMouseReleased() const;
			bool DECLSPEC Quit();
			void DECLSPEC startRecordingTextInput(int maxcharacters, std::string* stream);
			void DECLSPEC stopRecordingTextInput(std::string* stream);

			void DECLSPEC getMouseState(int& x, int& y) const;
			void setMouseState(int&x, int& y);

			void setQuitState(bool quit);
			void updateKeyState(int key, KeyState state);
			void updateMouseState(uint8_t button, KeyState state);
			void updateTextInput(const char* text);
			void handleBackspace();
			void clear();

		private:
			bool _quit;
			// Numbers chosen above the max 512 button defined in SDL
			enum MouseButtons {LEFT = 800, RIGHT = 801, MIDDLE = 802};
			std::unique_ptr<std::vector<Input::KeyState*>> _toupdate; // pointer to do warnings about exposing std in a dll. different platforms have different implementations
			KeyState _activekeys[MAXKEYS]; // At least all the SDL_SCANCODES and room for possibly more?

			std::vector<RecordStream> _recordstreams;
			int _activestringlength;
			int _activestream;

			int _mousex;
			int _mousey;
	};

}