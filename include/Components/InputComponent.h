#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include "../../include/ECSFramework/Component.h"
#include "../Config/ComponentDefines.h"
#include <unordered_map>

const std::vector<std::string> KeyboardInputs = { 
	"MOVE_LEFT",
	"MOVE_RIGHT",
	"MOVE_UP",
	"MOVE_DOWN",
	"MELEE"
};

struct Key
{
	int scancode;
	bool pressed;
	bool held;

	Key(int scancode) : scancode(scancode), pressed(false), held(false) {}
};

// Proof of concept stage
// Do I need a released state?
class InputComponent : public Component
{
    public:
        static const uint_fast64_t ID = InputComponentID;

		InputComponent() 
		{
			keyboardinput_.insert({ KeyboardInputs[0], Key(SDL_SCANCODE_A) });
			keyboardinput_.insert({ KeyboardInputs[1], Key(SDL_SCANCODE_D) });
			keyboardinput_.insert({ KeyboardInputs[2], Key(SDL_SCANCODE_W) });
			keyboardinput_.insert({ KeyboardInputs[3], Key(SDL_SCANCODE_S) });
			keyboardinput_.insert({ KeyboardInputs[4], Key(SDL_SCANCODE_E) });
		}

        InputComponent(const InputComponent& c) {}

        virtual ~InputComponent() {}

        uint_fast64_t UniqueBits() const {return ID;}

		int Scancode(std::string input) { return keyboardinput_.at(input).scancode; }
		void SetScancode(std::string input, int scancode) { keyboardinput_.at(input).scancode = scancode; }

		bool Pressed(std::string input) { return keyboardinput_.at(input).pressed; }
		bool Held(std::string input) { return keyboardinput_.at(input).held; }

		void SetPressed(std::string input, bool state) { keyboardinput_.at(input).pressed = state; }
		void SetHeld(std::string input, bool state) { keyboardinput_.at(input).held = state; }

    private:
		std::unordered_map<std::string, Key> keyboardinput_;

};

#endif // INPUTCOMPONENT_H
