#pragma once
#include <memory>
#include "GUIManager.h"
#include "StateFramework/GameState.h"
#include "Components/DescriptionComponent.h"
#include "Components/StatsComponent.h"
#include "Config/GeneralConfig.h"
#include "GUIComponents/ValueComponent.h"
#include "GameMechanics/StatGenerator.h"

struct PlayerInfo;
class CharacterCreationState : public GameStateImpl
{
public:
	CharacterCreationState(const GeneralConfig& config, PlayerInfo* player);
	~CharacterCreationState();

	int InitializeState(SAS_System::Renderer& renderer, const SAS_System::Input& input);
	int UpdateState(int elapsedtime, SAS_System::Renderer& renderer, const SAS_System::Input& input);
	int TransitionIntoState(SAS_System::Renderer& renderer);
	int TransitionFromState(SAS_System::Renderer& renderer);
	int NextState() { return _nextstate; }

private:
	// Config Structs
	GeneralConfig _generalconfig;

	int _nextstate;
	SAS_GUI::GUIManager _guimanager;
	
	int _availablestatpoints;

	// Character Components
	DescriptionComponent _characterdescription;
	MainStatMap _defaultstats;
	PlayerInfo* _playerinfo;	// Player info shared between states
	StatGenerator _generator;
	std::unordered_map<std::string, SAS_GUI::ValueComponent<std::string>*> _valuecomponentmap;

};

