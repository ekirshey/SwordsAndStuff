#include <iostream>
#include "../../../include/GameStates/States/MainMenuState.h"
#include "../../../include/SDL/SDLManager.h"
#include "../../../include/Systems/RenderSystem.h"
#include "../../../include/Components/RenderComponent.h"
#include "../../../include/Components/PositionComponent.h"
#include "../../../include/GameStates/States/GameRunningState.h"
#include "../../../include/GameStates/States/CharacterCreationState.h"

MainMenuState::MainMenuState(bool persistent) : GameState(persistent)
{
    SetCurrentState(INITIALIZE);
}

MainMenuState::~MainMenuState()
{

}

void MainMenuState::InitializeState()
{
    std::cout << "Initialize" << std::endl;
	//std::string path = "media\\backgrounds\\mainmenubg.bmp";
	//path = "media\\buttons\\startbutton.bmp";
    // Build systems and entities


    SetCurrentState(TRANSITIONIN);
}

void MainMenuState::TransitionIntoState()
{
    std::cout << "Transition Into State" << std::endl;
    SetCurrentState(UPDATE);
}

void MainMenuState::UpdateState(int elapsedtime)
{
	auto keyboardstate_ = sdlmanager_->GetKeyBoardState();
	
	if (keyboardstate_[SDL_SCANCODE_C]) {
		nextstate_ = std::make_unique<CharacterCreationState>(false);
		SetCurrentState(TRANSITIONOUT);
	}
	else if (keyboardstate_[SDL_SCANCODE_Q]) {
		SetCurrentState(TRANSITIONOUT);
	}
}

void MainMenuState::TransitionFromState()
{
    std::cout << "Transition From State" << std::endl;

    std::cout << "Exit State" << std::endl;

	
    SetCurrentState(EXIT);
}



