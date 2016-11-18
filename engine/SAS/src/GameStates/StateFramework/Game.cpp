#include "Config/GameDefines.h"
#include "GameStates/StateFramework/Game.h"
#include "GameStates/StateFramework/GameState.h"
#include <iostream>
#include <sstream>

// TODO
const int SCREEN_FPS = 1000;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

// Im doing this pretty barebones for now since this isn't the main focus of this quicky game project.
// I don't want to get bogged down with perfecting something that could be done as an enum essentially

Game::Game(int x, int y) 
	: _gamestates()
	, _activestate(0)
	, _gamerunning(true)
	, _renderer(x, y)
	, _input()
{
	_gamestates.resize(NUM_STATES);
}

Game::~Game()
{
    //dtor
}

void Game::RemoveStateAtIndex(int idx)
{

}

void Game::Run()
{
	int currenttime = 0;
	int previoustime = 0;
	int framecounter = 0;

	// If everything initialized ok then enter main game loop
	std::cout << "Finished Game Init" << std::endl;
	std::cout << "Entering Main Loop" << std::endl << std::endl;

	currenttime = SAS_System::CurrentTicks();

	// Main Game Loop
	while (_gamerunning)
	{
		previoustime = currenttime;
		currenttime = SAS_System::CurrentTicks();

		_renderer.ClearScreen();

		// Read the event queue so the state has the input
		SAS_System::UpdateInput(&_input);
		_gamerunning = !_input.Quit();
		if (_gamerunning) {
			Update(currenttime - previoustime);
			_renderer.Update();
		}

		framecounter++;
	}   // End Main Loop

	SAS_System::ShutdownSystem();
}

void Game::Update(int elapsedtime)
{
    _activestate =_gamestates[_activestate]->FiniteStateMachine(elapsedtime);
	// Invalid next state
	if (_activestate >= _gamestates.size() || _activestate < 0) {
		_gamerunning = false;
	}
}
