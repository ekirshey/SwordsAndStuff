#include <iostream>
#include "MainMenuState.h"
#include "RenderSystem.h"
#include "RenderComponent.h"
#include "PositionComponent.h"
#include "GameRunningState.h"
#include "CharacterCreationState.h"
#include "Config/GameDefines.h"
//GUI Includes
#include "GUIViews/ButtonView.h"
#include "GUIComponents/Button.h"
#include "GUIDynamics/Dynamics.h"

MainMenuState::MainMenuState(const GeneralConfig& config )
	: _nextstate(MAINMENU_IDX)
	, _exit(false)
	, _generalconfig(config)
{
}

MainMenuState::~MainMenuState()
{

}

int MainMenuState::InitializeState(SAS_System::Renderer& renderer, const SAS_System::Input& input)
{
    std::cout << "Initialize" << std::endl;
	//std::string path = "media\\backgrounds\\mainmenubg.bmp";
	//path = "media\\buttons\\startbutton.bmp";
    // Build systems and entities

	SAS_GUI::WindowView wv( SDL_Rect{0,0,SCREEN_WIDTH,SCREEN_HEIGHT}, _generalconfig.mediaroot + "media\\backgrounds\\mainmenubg.bmp");
	auto mainwindow = std::make_unique<SAS_GUI::Window>(SDL_Rect{ 0,0,SCREEN_WIDTH,SCREEN_HEIGHT }, &renderer, "mainmenu", wv,  true);

	SAS_GUI::ButtonView bv(SDL_Rect{ 0,0,60,20 },
		_generalconfig.mediaroot + "media\\buttons\\startbutton.bmp");

	mainwindow->AddComponent<SAS_GUI::Button>(SDL_Rect{ 200, 200, 60, 20 }, bv, 
		[this]() {
			_nextstate = CHARCREATION_IDX;
			_exit = true;
		}
	);

	_guimanager.AddWindow(std::move(mainwindow));

#ifdef FOO
	window->AddComponent<SAS_GUI::GUIButton>(SDL_Rect{ 610,450,60,20 }, SDL_Rect{ 0,0,60,20 }, "../../../media/buttons/startbutton.bmp", 
		std::unique_ptr<LoadNextState<GameRunningState>>(new LoadNextState<GameRunningState>(this)));
	//window->AddComponent<GUIButton>(SDL_Rect{ 610,500,60,20 }, SDL_Rect{ 0,0,60,20 }, "../../../media/buttons/startbutton.bmp");
	guimanager_->AddWindow(std::move(window));
#endif
	return TRANSITIONIN;
}

int MainMenuState::TransitionIntoState(SAS_System::Renderer& renderer)
{
    std::cout << "Transition Into State" << std::endl;
	
	return UPDATE;
}

int MainMenuState::UpdateState(int elapsedtime, SAS_System::Renderer& renderer, const SAS_System::Input& input)
{
	int ret = UPDATE;

	_guimanager.Update(elapsedtime, input);
	_guimanager.Render(&renderer);

	if (_exit) {
		ret = TRANSITIONOUT;
	}

	return ret;
}

int MainMenuState::TransitionFromState(SAS_System::Renderer& renderer)
{
    std::cout << "Transition From State" << std::endl;

    std::cout << "Exit State" << std::endl;
	
	return EXIT;
}
