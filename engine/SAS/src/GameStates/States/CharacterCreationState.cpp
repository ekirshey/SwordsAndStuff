#include <iostream>
#include <vector>
#include "GameStates/States/CharacterCreationState.h"
#include "GameStates/States/GameRunningState.h"
#include "Config/GameDefines.h"

#include "GUIViews/ButtonView.h"
#include "GUIViews/DropdownMenuView.h"
#include "GUIComponents/Label.h"
#include "GUIComponents/TextBox.h"
#include "GUIComponents/Button.h"
#include "GUIComponents/DynamicText.h"
#include "GUIComponents/DropdownMenu.h"

CharacterCreationState::CharacterCreationState(const GeneralConfig& config)
	: _generalconfig(config)
	, _nextstate(CHARCREATION_IDX)
	, _availablestatpoints(10)
{
}


CharacterCreationState::~CharacterCreationState()
{

}

int CharacterCreationState::InitializeState(SAS_System::Renderer& renderer, const SAS_System::Input& input) {

	SAS_GUI::WindowView wv(SDL_Rect{ 0,0,SCREEN_WIDTH,SCREEN_HEIGHT }, SDL_Rect{0,0,SCREEN_WIDTH,SCREEN_HEIGHT}, _generalconfig.mediaroot + "media\\backgrounds\\character_creation_bg.bmp");
	auto mainwindow = std::make_unique<SAS_GUI::Window>(&renderer, "mainmenu", wv,  true);

	SAS_GUI::TextView tv(18, SDL_Color{ 255,0,0 }, _generalconfig.mediaroot + "media\\font.ttf", SDL_Rect{50,10,100,100});
	auto namelabel = std::make_unique<SAS_GUI::Label>(tv, "Name:");
	
	SAS_GUI::DropdownMenuView ddv(SDL_Rect{ 400,400,100,20 }, SDL_Rect{ 400,410,100,20 });
	mainwindow->AddComponent<SAS_GUI::DropdownMenu>(ddv, tv, std::vector<std::string>{"a"});

	tv.position = SDL_Rect{ 100, 10, 60, 20 };
	auto namebox = std::make_unique<SAS_GUI::TextBox>(tv);
	_valuecomponentmap["NameBox"] = namebox.get();
	mainwindow->AddComponent(std::move(namebox));
	mainwindow->AddComponent(std::move(namelabel));

	tv.position = SDL_Rect{ 50, 40, 60, 20 };
	mainwindow->AddComponent<SAS_GUI::Label>(tv, "Available Points:");

	tv.position = SDL_Rect{ 250, 40, 60, 20 };
	mainwindow->AddComponent<SAS_GUI::DynamicText<int>>(tv, _availablestatpoints);

	// Stat Labels
	tv.position = SDL_Rect{ 50, 70, 60, 20 };
	mainwindow->AddComponent<SAS_GUI::Label>(tv, "Strength:");

	tv.position = SDL_Rect{ 250, 70, 60, 20 };
	mainwindow->AddComponent<SAS_GUI::DynamicText<float>>(tv, _characterstats.stats_[STRENGTH]);

	SAS_GUI::ButtonView bv(SDL_Rect{ 200, 200, 25, 25 }, SDL_Rect{ 0,0,25,25 },
		_generalconfig.mediaroot + "media\\buttons\\arrows.bmp");

	mainwindow->AddComponent<SAS_GUI::Button>(bv, 
		[this]() {
			if (_availablestatpoints > 0) {
				_availablestatpoints--;
				_characterstats.SetStat(STRENGTH, _characterstats.GetStat(STRENGTH) + 1);
			}
		}
	);

	bv.position = SDL_Rect{ 200, 245, 25, 25};
	mainwindow->AddComponent<SAS_GUI::Button>(bv, 
		[this]() {
			if (_availablestatpoints > 0) {
				_availablestatpoints--;
				_characterstats.SetStat(INTELLIGENCE, _characterstats.GetStat(INTELLIGENCE) + 1);
			}
		}
	);

	tv.position = SDL_Rect{ 50, 90, 60, 20 };
	mainwindow->AddComponent<SAS_GUI::Label>(tv, "Intelligence:");

	tv.position = SDL_Rect{ 250, 90, 60, 20 };
	mainwindow->AddComponent<SAS_GUI::DynamicText<float>>(tv, _characterstats.stats_[INTELLIGENCE]);

	tv.position = SDL_Rect{ 50, 110, 60, 20 };
	mainwindow->AddComponent<SAS_GUI::Label>(tv, "Health:");

	tv.position = SDL_Rect{ 250, 110, 60, 20 };
	mainwindow->AddComponent<SAS_GUI::DynamicText<float>>(tv, _characterstats.stats_[HEALTH]);

	tv.position = SDL_Rect{ 50, 130, 60, 20 };
	mainwindow->AddComponent<SAS_GUI::Label>(tv, "Mana:");

	tv.position = SDL_Rect{ 250, 130, 60, 20 };
	mainwindow->AddComponent<SAS_GUI::DynamicText<float>>(tv, _characterstats.stats_[MANA]);

	_guimanager.AddWindow(std::move(mainwindow));
	//SAS_GUI::GUIBuilder::BuildGUIFromFile(_guimanager.get(), "../../../config/gui/charcreationconfig.txt");
/*
	auto window = std::make_unique<Window>(GetSDLManager(), "mainmenu", SDL_Rect{ 0, 0, 1280, 640 }, "../../../media//backgrounds/charcreationbg.bmp", "../../../media/backgrounds/charcreationbg.bmp", true);

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

	_guimanager->AddWindow(std::move(window));
*/
	return TRANSITIONIN;
}



int CharacterCreationState::UpdateState(int elapsedtime, SAS_System::Renderer& renderer, const SAS_System::Input& input) {
	int ret = UPDATE;

	_guimanager.Update(elapsedtime, input);
	_guimanager.Render(&renderer);
	if (input.isKeyPressed(SDL_SCANCODE_Q)) {
		_characterdescription._name = _valuecomponentmap["NameBox"]->GetValue();
		std::cout << _characterdescription._name << std::endl;
	}

	return ret;
}

int CharacterCreationState::TransitionIntoState(SAS_System::Renderer& renderer) {
	std::cout << "Entering Character Creation state Update!" << std::endl;
	return UPDATE;
}

int CharacterCreationState::TransitionFromState(SAS_System::Renderer& renderer) {
	return EXIT;
}