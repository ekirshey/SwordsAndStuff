#include "../../../include/GameStates/StateFramework/GameStateManager.h"
#include "../../../include/GameStates/StateFramework/GameState.h"
#include "SDLManager.h"
#include <iostream>
#include <sstream>

// TODO
const int SCREEN_FPS = 1000;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

// Im doing this pretty barebones for now since this isn't the main focus of this quicky game project.
// I don't want to get bogged down with perfecting something that could be done as an enum essentially

GameStateManager::GameStateManager() : gamestates_()
{
    activestate_ = 0;
    gamerunning_ = true;
}

GameStateManager::~GameStateManager()
{
    //dtor
}

void GameStateManager::AddState(std::unique_ptr<GameState> state)
{
	if (state != nullptr) {
		gamestates_.push_back(std::move(state));
		gamestates_.back()->AssignSDLManager(&sdlmanager_);
	}
}

void GameStateManager::RemoveStateAtIndex(int idx)
{

}

void GameStateManager::Run()
{
    int currenttime = 0;
	int previoustime = 0;
	int framecounter = 0;

    // If everything initialized ok then enter main game loop
    if (Initialize())
    {
        sdlmanager_.Start();

        std::cout << "Finished GameStateManager Init" << std::endl;
        std::cout << "Entering Main Loop" << std::endl << std::endl;

		currenttime = SDL_GetTicks();
        // Main Game Loop
        while(gamerunning_)
        {
			previoustime = currenttime;
			currenttime = SDL_GetTicks();

            // Clear the Screen
            sdlmanager_.ClearScreen();

            // Read the event queue so the state has the input
            if (sdlmanager_.ReadEventQueue())
                gamerunning_ = false;   // Quit event was received
            else
            {
                Update(currenttime-previoustime);
                sdlmanager_.Render();
            }

            framecounter++;
/*		
			// REplaced with VSYNC
            int frameTicks = SDL_GetTicks() - currenttime;

            if( frameTicks < SCREEN_TICK_PER_FRAME )
            {
                //Wait remaining time
                SDL_Delay( SCREEN_TICK_PER_FRAME - frameTicks );
            }
*/
        }   // End Main Loop

        sdlmanager_.Close();
    }
}

bool GameStateManager::Initialize()
{
    return sdlmanager_.Initialize();
}

void GameStateManager::Update(int elapsedtime)
{
    gamestates_[activestate_]->FiniteStateMachine(elapsedtime);
    if (gamestates_[activestate_]->GetCurrentState() == EXIT)
    {
		if (gamestates_[activestate_]->HasNextState()) {
			auto nextstate = gamestates_[activestate_]->PopNextState();
			if (gamestates_[activestate_]->IsPersistent()) {
				gamestates_[activestate_]->SetCurrentState(TRANSITIONIN);
			}
			else // Remove a non persistent state
				RemoveLastState();
			
			AddState(std::move(nextstate));
			activestate_++;
		}
		else if (activestate_ > 0) {// If there is no next state and a persistent state underneath then go to that
			RemoveLastState();
		}
		else {	// If possible move to next pre existing state
			// Check for anymore valid states, if none then exit
			if (++activestate_ >= gamestates_.size())
				gamerunning_ = false;
		}
    }
}
