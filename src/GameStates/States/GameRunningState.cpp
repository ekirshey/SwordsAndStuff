#include <iostream>
#include "../../../include/GameStates/States/GameRunningState.h"
#include "../../../include/SDL/SDLManager.h"
#include "../../../include/SubSystems/MonsterSpawner.h"

GameRunningState::GameRunningState()
{
    SetCurrentState(INITIALIZE);
}

GameRunningState::~GameRunningState()
{

}

void GameRunningState::InitializeState()
{
    SDL_Rect camerarect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};

    // Create Game World and Camera
    gameworld_ = std::unique_ptr<GameWorld>(new GameWorld(3072,2560));
    gameworld_->BuildProceduralTileMap(32);
    camera_ = std::unique_ptr<Camera>(new Camera(gameworld_->Width(), gameworld_->Height(),camerarect ));

	// Set up Objects
	objectmanager_ = std::unique_ptr<ObjectManager>(new ObjectManager(GetSDLManager(), gameworld_.get(), camera_.get()));

	// GUI Setup HUD and GUI separate for now
    //hudmanager_ = std::unique_ptr<HUDManager>(new HUDManager(objectmanager_.get(), GetSDLManager()));
	//guimanager_ = std::unique_ptr<GUIManager>(new GUIManager(GetSDLManager(), "keymapfile.txt","guifile.txt"));

    SetCurrentState(TRANSITIONIN);
}

void GameRunningState::TransitionIntoState()
{
    std::cout << "Game Running: Transition Into State" << std::endl;
    SetCurrentState(UPDATE);
}

void GameRunningState::UpdateState(int elapsedtime)
{
    objectmanager_->Update(elapsedtime);
    //hudmanager_->Update();
}

void GameRunningState::TransitionFromState()
{
    std::cout << "Game Running: Transition From State" << std::endl;

    std::cout << "Game Running: Exit State" << std::endl;
    SetCurrentState(EXIT);
}



