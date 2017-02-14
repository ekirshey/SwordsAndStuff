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
#include "GUIBuilder.h"

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
	std::cout << "Initialize Main Menu" << std::endl;
	SAS_GUI::GUIBuilder::CallbackMap callbacks;
	callbacks.insert({ "start_button",
		[this]() {
		_nextstate = CHARCREATION_IDX;
		_exit = true;
		}
	});

	SAS_GUI::GUIBuilder::BuildGUIFromFile(&_guimanager, renderer, _generalconfig.mediaroot, _generalconfig.guiconfig, callbacks);

	
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
