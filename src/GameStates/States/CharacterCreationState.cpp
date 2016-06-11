#include <iostream>
#include <vector>
#include "../../../include/GameStates/States/CharacterCreationState.h"
#include "../../../include/GameStates/States/GameRunningState.h"
#include "../../../include/SDL/SDLManager.h"
#include "../../../include/GUI/GUIComponents/TextBox.h"
#include "../../../include/GUI/GUIComponents/DynamicText.h"
#include "../../../include/GUI/GUIComponents/GUIImage.h"
#include "../../../include/GUI/GUIComponents/GUIButton.h"
#include "../../../include/GUI/GUIBuilder.h"

class IncrementClip {
public:
	IncrementClip(GUIImage* image) : image_(image) {}
	void operator()() {
		image_->NextClip();
	}

private:
	GUIImage* image_;
};

class DecrementClip {
public:
	DecrementClip(GUIImage* image) : image_(image) {}
	void operator()() {
		image_->PreviousClip();
	}

private:
	GUIImage* image_;
};

CharacterCreationState::CharacterCreationState(bool persistent) : GameState(persistent)
{
	SetCurrentState(INITIALIZE);
}


CharacterCreationState::~CharacterCreationState()
{

}

void CharacterCreationState::InitializeState() {

	guimanager_ = std::make_unique<GUIManager>(GetSDLManager());

	GUIBuilder::BuildGUIFromFile(guimanager_.get(), "../../../config/gui/charcreationconfig.txt");
/*
	auto window = std::make_unique<GUIWindow>(GetSDLManager(), "mainmenu", SDL_Rect{ 0, 0, 1280, 640 }, "../../../media//backgrounds/charcreationbg.bmp", "../../../media/backgrounds/charcreationbg.bmp", true);

	window->AddComponent<TextBox>(&characterDescription.name_, SDL_Rect{ 200, 200, 100, 25 }, 20, SDL_Color{ 0,0,0,255 }, "..\\..\\..\\media\\font.ttf");
	window->AddComponent<DynamicText>(&characterDescription.name_, SDL_Rect{ 400, 200, 100, 25 }, 20, SDL_Color{ 255,0,0,255 }, "..\\..\\..\\media\\font.ttf");

	auto image = std::make_unique<GUIImage>("../../../media/sprites/Pawns.png", SDL_Point{ 300,300 },
		std::vector<SDL_Rect>{
		SDL_Rect{ 0, 0, 22,28 },
			SDL_Rect{ 22, 0, 22,28 },
			SDL_Rect{ 44, 0, 22,28 },
			SDL_Rect{ 66, 0, 22,28 },
			SDL_Rect{ 88, 0, 22,28 },
			SDL_Rect{ 0, 28, 22,28 },
			SDL_Rect{ 22, 28, 22,28 },
			SDL_Rect{ 44, 28, 22,28 },
			SDL_Rect{ 66, 28, 22,28 },
			SDL_Rect{ 88, 28, 22,28 }
	});

	window->AddComponent<GUIButton<IncrementClip>>(SDL_Rect{ 250,300,60,20 }, SDL_Rect{ 0,0,25,25 }, "../../../media/buttons/arrows.bmp", IncrementClip(image.get()));
	window->AddComponent<GUIButton<DecrementClip>>(SDL_Rect{ 350,300,60,20 }, SDL_Rect{ 25,0,25,25 }, "../../../media/buttons/arrows.bmp", DecrementClip(image.get()));

	window->AddComponent(std::move(image));

	guimanager_->AddWindow(std::move(window));
*/
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