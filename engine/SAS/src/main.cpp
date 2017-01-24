#include <iostream>
#include "FileParser/cpptoml.h"
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

	std::string rootconfigloc = argv[1];
	// Default paths
	const std::string laptoppath  = "C:\\cygwin64\\home\\prome\\code\\SwordsAndStuff\\";
	const std::string desktoppath = "F:\\github\\SwordsAndStuff\\";

	GeneralConfig config;

	auto rootconfig = cpptoml::parse_file(rootconfigloc);
	auto title = rootconfig->get_as<std::string>("title");
	config.configroot = rootconfig->get_as<std::string>("configpath").value_or(desktoppath + "config");
	config.mediaroot = rootconfig->get_as<std::string>("mediapath").value_or(desktoppath + "media");

    // Set up the Game State Manager
    Game gamestatemanager(SCREEN_WIDTH, SCREEN_HEIGHT);
	
    // Add states
	config.guiconfig = config.configroot + rootconfig->get_qualified_as<std::string>("mainmenu.guiconfig").value_or(desktoppath + "config\\gui\\mainmenugui.toml");
	gamestatemanager.AddState<MainMenuState>(true, MAINMENU_IDX, config);

	config.guiconfig = config.configroot + rootconfig->get_qualified_as<std::string>("charactercreation.guiconfig").value_or(desktoppath + "config\\gui\\charcreationgui.toml");
	gamestatemanager.AddState<CharacterCreationState>(false, CHARCREATION_IDX, config);

	config.guiconfig = config.configroot + rootconfig->get_qualified_as<std::string>("gamerunning.guiconfig").value_or(desktoppath + "config\\gui\\gamegui.toml");
	gamestatemanager.AddState<GameRunningState>(false, GAMERUNNING_IDX, config);

    // Loop forever
    gamestatemanager.Run();

	getchar();
    return 0;
}
