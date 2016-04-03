#include <iostream>
#include "../../../include/GameStates/States/CharacterCreationState.h"
#include "../../../include/GameStates/States/GameRunningState.h"
#include "../../../include/SDL/SDLManager.h"


CharacterCreationState::CharacterCreationState(bool persistent) : GameState(persistent)
{
	SetCurrentState(INITIALIZE);
}


CharacterCreationState::~CharacterCreationState()
{

}

void CharacterCreationState::InitializeState() {
	SetCurrentState(TRANSITIONIN);
}

void CharacterCreationState::TransitionIntoState() {
	std::cout << "Entering Character Creation state Update!" << std::endl;
	SetCurrentState(UPDATE);
}

void CharacterCreationState::UpdateState(int elapsedtime) {

	auto keyboardstate_ = sdlmanager_->GetKeyBoardState();

	if (keyboardstate_[SDL_SCANCODE_RETURN]) {
		nextstate_ = std::make_unique<GameRunningState>(true);
		SetCurrentState(TRANSITIONOUT);
	}
}

void CharacterCreationState::TransitionFromState() {
	SetCurrentState(EXIT);
}