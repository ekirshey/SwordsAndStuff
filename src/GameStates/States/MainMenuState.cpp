#include <iostream>
#include "../../../include/GameStates/States/MainMenuState.h"
#include "../../../include/SDL/SDLManager.h"
#include "../../../include/Systems/RenderSystem.h"
#include "../../../include/Components/RenderComponent.h"
#include "../../../include/Components/PositionComponent.h"
#include "../../../include/GameStates/States/GameRunningState.h"
#include "../../../include/GameStates/States/CharacterCreationState.h"
#include "../../../include/GUI/GUIComponents/GUIButton.h"

class LoadCharacterCreation {
public:
	LoadCharacterCreation(GameState* state) : state_(state){}
	void operator()() {
		state_->AddNextState(std::make_unique<CharacterCreationState>(false));
		state_->SetCurrentState(TRANSITIONOUT);
	}

private:
	GameState* state_;
};

class LoadGameRunningState {
public:
	LoadGameRunningState(GameState* state) : state_(state) {}
	void operator()() {
		state_->AddNextState(std::make_unique<GameRunningState>(true));
		state_->SetCurrentState(TRANSITIONOUT);
	}

private:
	GameState* state_;
};


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
	guimanager_ = std::make_unique<GUIManager>(GetSDLManager());
	auto window = std::make_unique<GUIWindow>(GetSDLManager(), "mainmenu", SDL_Rect{ 0, 0, 1280, 640 }, "../../../media//backgrounds/mainmenubg.bmp", "../../../media/backgrounds/mainmenubg.bmp", true);
	window->AddComponent<GUIButton<LoadCharacterCreation>>(SDL_Rect{ 610,400,60,20 }, SDL_Rect{ 0,0,60,20 }, "../../../media/buttons/startbutton.bmp", LoadCharacterCreation(this) );
	window->AddComponent<GUIButton<LoadGameRunningState>>(SDL_Rect{ 610,450,60,20 }, SDL_Rect{ 0,0,60,20 }, "../../../media/buttons/startbutton.bmp", LoadGameRunningState(this));
	//window->AddComponent<GUIButton>(SDL_Rect{ 610,500,60,20 }, SDL_Rect{ 0,0,60,20 }, "../../../media/buttons/startbutton.bmp");
	guimanager_->AddWindow(std::move(window));

    SetCurrentState(TRANSITIONIN);
}

void MainMenuState::TransitionIntoState()
{
    std::cout << "Transition Into State" << std::endl;
	
    SetCurrentState(UPDATE);
}

void MainMenuState::UpdateState(int elapsedtime)
{
	auto keyboardstate = GetSDLManager()->GetKeyBoardState();

	guimanager_->Update(elapsedtime);

	if (keyboardstate[SDL_SCANCODE_Q]) {
		SetCurrentState(TRANSITIONOUT);
	}
}

void MainMenuState::TransitionFromState()
{
    std::cout << "Transition From State" << std::endl;

    std::cout << "Exit State" << std::endl;
	
    SetCurrentState(EXIT);
}



