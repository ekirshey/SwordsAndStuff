#include <iostream>
#include "../../../include/GameStates/States/CharacterCreationState.h"
#include "../../../include/GameStates/States/GameRunningState.h"
#include "../../../include/SDL/SDLManager.h"
#include "../../../include/GUI/GUIComponents/TextBox.h"
#include "../../../include/GUI/GUIComponents/DynamicText.h"
#include "../../../include/GUI/GUIComponents/GUIImage.h"

CharacterCreationState::CharacterCreationState(bool persistent) : GameState(persistent)
{
	SetCurrentState(INITIALIZE);
}


CharacterCreationState::~CharacterCreationState()
{

}

void CharacterCreationState::InitializeState() {

	guimanager_ = std::make_unique<GUIManager>(GetSDLManager());
	auto window = std::make_unique<GUIWindow>(GetSDLManager(), "mainmenu", SDL_Rect{ 0, 0, 1280, 640 }, "../../../media//backgrounds/charcreationbg.bmp", "../../../media/backgrounds/charcreationbg.bmp", true);

	window->AddComponent<TextBox>(&characterDescription.name_, SDL_Rect{ 200, 200, 100, 25 }, 20, SDL_Color{ 0,0,0,255 }, "..\\..\\..\\media\\font.ttf");
	window->AddComponent<DynamicText>(&characterDescription.name_, SDL_Rect{ 400, 200, 100, 25 }, 20, SDL_Color{ 255,0,0,255 }, "..\\..\\..\\media\\font.ttf");
	window->AddComponent<GUIImage>("../../../media/sprites/tree.png", SDL_Rect{ 300,300,222,223 });

	guimanager_->AddWindow(std::move(window));

	SetCurrentState(TRANSITIONIN);
}

void CharacterCreationState::TransitionIntoState() {
	std::cout << "Entering Character Creation state Update!" << std::endl;
	SetCurrentState(UPDATE);
}

void CharacterCreationState::UpdateState(int elapsedtime) {

	auto keyboardstate_ = GetSDLManager()->GetKeyBoardState();

	guimanager_->Update(elapsedtime);

	if (keyboardstate_[SDL_SCANCODE_RETURN]) {
		AddNextState(std::make_unique<GameRunningState>(true));
		SetCurrentState(TRANSITIONOUT);
	}
}

void CharacterCreationState::TransitionFromState() {
	SetCurrentState(EXIT);
}