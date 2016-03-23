#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include "../../include/ECSFramework/Component.h"
#include "../Config/ComponentDefines.h"
#include <unordered_map>

enum INPUTS { MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN, MELEE };

const std::vector<int> KeyboardInputs{
	MOVE_LEFT, 
	MOVE_RIGHT, 
	MOVE_UP, 
	MOVE_DOWN, 
	MELEE
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
			keyboardinput_.insert({ MOVE_LEFT, Key(SDL_SCANCODE_A) });
			keyboardinput_.insert({ MOVE_RIGHT, Key(SDL_SCANCODE_D) });
			keyboardinput_.insert({ MOVE_UP, Key(SDL_SCANCODE_W) });
			keyboardinput_.insert({ MOVE_DOWN, Key(SDL_SCANCODE_S) });
			keyboardinput_.insert({ MELEE, Key(SDL_SCANCODE_E) });
		}

        InputComponent(const InputComponent& c) {}

        ~InputComponent() {}

        uint_fast64_t UniqueBits() const {return ID;}

		int Scancode(int input) { return keyboardinput_.at(input).scancode; }
		void SetScancode(int input, int scancode) { keyboardinput_.at(input).scancode = scancode; }

		bool Pressed(int input) { return keyboardinput_.at(input).pressed; }
		bool Held(int input) { return keyboardinput_.at(input).held; }

		void SetPressed(int input, bool state) { keyboardinput_.at(input).pressed = state; }
		void SetHeld(int input, bool state) { keyboardinput_.at(input).held = state; }

    private:
		std::unordered_map<int, Key> keyboardinput_;

};

#endif // INPUTCOMPONENT_H
