#define MAIN

#ifdef MAIN
#include <iostream>
#include "GameStates/StateFramework/Game.h"
#include "GameStates/States/MainMenuState.h"
#include "GameStates/States/CharacterCreationState.h"
#include "GameStates/States/GameRunningState.h"
#include "SystemControl.h"
#include "Config/GameDefines.h"
#include "Config/GeneralConfig.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	// Initialize SDL and subsystems
	SAS_System::InitializeSystem();

    // Set up the Game State Manager
    Game gamestatemanager(SCREEN_WIDTH, SCREEN_HEIGHT);
	
	const std::string laptoppath  = "C:\\cygwin64\\home\\prome\\code\\SwordsAndStuff\\";
	const std::string desktoppath = "D:\\Github\\SwordsAndStuff\\";

	GeneralConfig config;
#ifdef LAPTOP
	config.mediaroot = laptoppath;
#else
	config.mediaroot = desktoppath;
#endif

    // Add states
	gamestatemanager.AddState<MainMenuState>(true, MAINMENU_IDX, config);
	gamestatemanager.AddState<CharacterCreationState>(false, CHARCREATION_IDX, config);
	gamestatemanager.AddState<GameRunningState>(false, GAMERUNNING_IDX, config);

    // Loop forever
    gamestatemanager.Run();

	getchar();
    return 0;
}

#endif