#include <SDL.h>    // Apparently need to include this where main is
#include <iostream>
#include "../include/GameStates/StateFramework/GameStateManager.h"
#include "../include/GameStates/States/MainMenuState.h"
#include "../include/GameStates/States/GameRunningState.h"
#include "../include/SDL/SDLManager.h"

// Messing with Awesomium integration
// Various included headers
int main(int argc, char *argv[])
{
    // Set up the Game State Manager
    GameStateManager gamestatemanager;

    // Add states
    gamestatemanager.AddState(new MainMenuState());
    gamestatemanager.AddState(new GameRunningState());

    // Loop forever
    gamestatemanager.Run();

    return 0;
}
