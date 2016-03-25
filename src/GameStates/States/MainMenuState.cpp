#include <iostream>
#include "../../../include/GameStates/States/MainMenuState.h"
#include "../../../include/SDL/SDLManager.h"
#include "../../../include/Systems/RenderSystem.h"
#include "../../../include/Components/RenderComponent.h"
#include "../../../include/Components/PositionComponent.h"

void StartButton(GameState* state)
{
    MainMenuState* currentstate = static_cast<MainMenuState*>(state);

    currentstate->SetCurrentState(TRANSITIONOUT);
}

MainMenuState::MainMenuState()
{
    SetCurrentState(INITIALIZE);
}

MainMenuState::~MainMenuState()
{

}

void MainMenuState::InitializeState()
{
    std::cout << "Initialize" << std::endl;

    // Build systems and entities
    ecsmanager_.AddSystem(std::make_unique<RenderSystem>(GetSDLManager()),0);

    // Background
    int backgroundentity = ecsmanager_.CreateEntity();
    SDL_Rect rect = {0,0,640,480};
    std::string path = "media\\backgrounds\\mainmenubg.bmp";
    ecsmanager_.AddComponentToEntity(backgroundentity, std::make_unique<PositionComponent>(0,0));
    ecsmanager_.AddComponentToEntity(backgroundentity, std::make_unique<RenderComponent>(path,rect, 0.0));

    // Start Button
    int startbuttonentity = ecsmanager_.CreateEntity();
    rect = {0,0,72,30};
    path = "media\\buttons\\startbutton.bmp";
    ecsmanager_.AddComponentToEntity(startbuttonentity, std::make_unique<RenderComponent>(path, rect, 0.0));
    ecsmanager_.AddComponentToEntity(startbuttonentity, std::make_unique<PositionComponent>(284,300));

    SetCurrentState(TRANSITIONIN);
}

void MainMenuState::TransitionIntoState()
{
    std::cout << "Transition Into State" << std::endl;
    SetCurrentState(UPDATE);
}

void MainMenuState::UpdateState(int elapsedtime)
{
    //ecsmanager_.Process();
    SetCurrentState(EXIT);
}

void MainMenuState::TransitionFromState()
{
    std::cout << "Transition From State" << std::endl;

    std::cout << "Exit State" << std::endl;
    SetCurrentState(EXIT);
}



