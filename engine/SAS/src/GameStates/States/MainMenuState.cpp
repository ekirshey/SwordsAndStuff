#include <iostream>
#include "MainMenuState.h"
#include "SDLManager.h"
#include "RenderSystem.h"
#include "RenderComponent.h"
#include "PositionComponent.h"
#include "GameRunningState.h"
#include "CharacterCreationState.h"
#include "GUIButton.h"


template<typename T>
class LoadNextState : public SAS_GUI::ButtonFunction {
public:
	LoadNextState(GameState* state) : state_(state){}
	void operator()() {
		state_->AddNextState(std::make_unique<T>(false));
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
	guimanager_ = std::make_unique<SAS_GUI::GUIManager>(GetSDLManager());
	auto window = std::make_unique<SAS_GUI::GUIWindow>(GetSDLManager(), "mainmenu", SDL_Rect{ 0, 0, 1280, 640 }, "../../../media//backgrounds/mainmenubg.bmp", "../../../media/backgrounds/mainmenubg.bmp", true);
	//window->AddComponent<GUIButton<LoadNextState<CharacterCreationState>>>(SDL_Rect{ 610,400,60,20 }, SDL_Rect{ 0,0,60,20 }, "../../../media/buttons/startbutton.bmp", this );
	//window->AddComponent<GUIButton<LoadNextState<GameRunningState>>>(SDL_Rect{ 610,450,60,20 }, SDL_Rect{ 0,0,60,20 }, "../../../media/buttons/startbutton.bmp", this );
	window->AddComponent<SAS_GUI::GUIButton>(SDL_Rect{ 610,400,60,20 }, SDL_Rect{ 0,0,60,20 }, "../../../media/buttons/startbutton.bmp", 
		std::unique_ptr<LoadNextState<CharacterCreationState>>(new LoadNextState<CharacterCreationState>(this)));
	window->AddComponent<SAS_GUI::GUIButton>(SDL_Rect{ 610,450,60,20 }, SDL_Rect{ 0,0,60,20 }, "../../../media/buttons/startbutton.bmp", 
		std::unique_ptr<LoadNextState<GameRunningState>>(new LoadNextState<GameRunningState>(this)));
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



