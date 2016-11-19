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

	SAS_GUI::WindowView wv(SDL_Rect{0,0,SCREEN_WIDTH,SCREEN_HEIGHT}, _generalconfig.mediaroot + "media\\backgrounds\\character_creation_bg.bmp");
	auto mainwindow = std::make_unique<SAS_GUI::Window>(SDL_Rect{ 0,0,SCREEN_WIDTH,SCREEN_HEIGHT }, &renderer, "mainmenu", wv,  true);

	SAS_GUI::TextView tv(18, SDL_Color{ 255,0,0 }, _generalconfig.mediaroot + "media\\font.ttf");
	auto namelabel = std::make_unique<SAS_GUI::Label>(SDL_Rect{50,10,100,100}, tv, "Name:");
	
	SAS_GUI::ButtonView dbv(SDL_Rect{ 0,0,25,25 },
		_generalconfig.mediaroot + "media\\buttons\\arrows.bmp");

	SAS_GUI::DropdownMenuView ddv(200, 200, SDL_Color{ 5,5,5,255 }, SDL_Color{ 0,0,0,255 }, SDL_Color{50,50,50,255}, dbv, tv);
	mainwindow->AddComponent<SAS_GUI::DropdownMenu>(renderer, SDL_Rect{100,400,100,tv.fontsize}, ddv, std::vector<std::string>{"a", "b", "c"});
	mainwindow->AddComponent<SAS_GUI::DropdownMenu>(renderer, SDL_Rect{210,400,100,tv.fontsize}, ddv, std::vector<std::string>{"a", "b", "c", "d", "e"});
	mainwindow->AddComponent<SAS_GUI::DropdownMenu>(renderer, SDL_Rect{320,400,100,tv.fontsize}, ddv, std::vector<std::string>{"a", "b", "c"});
	mainwindow->AddComponent<SAS_GUI::DropdownMenu>(renderer, SDL_Rect{430,400,100,tv.fontsize}, ddv, std::vector<std::string>{"a", "b", "c", "d"});
	mainwindow->AddComponent<SAS_GUI::DropdownMenu>(renderer, SDL_Rect{540,400,100,tv.fontsize}, ddv, std::vector<std::string>{"a", "b", "c"});

	auto namebox = std::make_unique<SAS_GUI::TextBox>(SDL_Rect{ 100, 10, 60, 20 }, tv);
	_valuecomponentmap["NameBox"] = namebox.get();
	mainwindow->AddComponent(std::move(namebox));
	mainwindow->AddComponent(std::move(namelabel));

	mainwindow->AddComponent<SAS_GUI::Label>(SDL_Rect{ 50, 40, 60, 20 }, tv, "Available Points:");

	mainwindow->AddComponent<SAS_GUI::DynamicText<int>>(SDL_Rect{ 250, 40, 60, 20 }, tv, _availablestatpoints);

	// Stat Labels
	mainwindow->AddComponent<SAS_GUI::Label>(SDL_Rect{ 50, 70, 60, 20 }, tv, "Strength:");

	mainwindow->AddComponent<SAS_GUI::DynamicText<float>>(SDL_Rect{ 250, 70, 60, 20 }, tv, _characterstats.stats_[STRENGTH]);

	SAS_GUI::ButtonView bv(SDL_Rect{ 0,0,25,25 },
		_generalconfig.mediaroot + "media\\buttons\\arrows.bmp");

	mainwindow->AddComponent<SAS_GUI::Button>(SDL_Rect{ 200, 200, 25, 25 }, bv, 
		[this]() {
			if (_availablestatpoints > 0) {
				_availablestatpoints--;
				_characterstats.SetStat(STRENGTH, _characterstats.GetStat(STRENGTH) + 1);
			}
		}
	);

	mainwindow->AddComponent<SAS_GUI::Button>(SDL_Rect{ 200, 245, 25, 25}, bv, 
		[this]() {
			if (_availablestatpoints > 0) {
				_availablestatpoints--;
				_characterstats.SetStat(INTELLIGENCE, _characterstats.GetStat(INTELLIGENCE) + 1);
			}
		}
	);

	mainwindow->AddComponent<SAS_GUI::Label>(SDL_Rect{ 50, 90, 60, 20 }, tv, "Intelligence:");
	mainwindow->AddComponent<SAS_GUI::DynamicText<float>>(SDL_Rect{ 250, 90, 60, 20 }, tv, _characterstats.stats_[INTELLIGENCE]);
	mainwindow->AddComponent<SAS_GUI::Label>(SDL_Rect{ 50, 110, 60, 20 }, tv, "Health:");
	mainwindow->AddComponent<SAS_GUI::DynamicText<float>>(SDL_Rect{ 250, 110, 60, 20 }, tv, _characterstats.stats_[HEALTH]);
	mainwindow->AddComponent<SAS_GUI::Label>(SDL_Rect{ 50, 130, 60, 20 }, tv, "Mana:");
	mainwindow->AddComponent<SAS_GUI::DynamicText<float>>(SDL_Rect{ 250, 130, 60, 20 }, tv, _characterstats.stats_[MANA]);

	_guimanager.AddWindow(std::move(mainwindow));

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