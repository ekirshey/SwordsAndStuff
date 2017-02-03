#pragma once

#include <memory>
#include "StateFramework/GameState.h"
#include "GameWorld/GameWorld.h"
#include "GameWorld/Camera.h"
#include "GUIManager.h"
#include "ECSFramework/ECSManager.h"
#include "GameMechanics/Spells/GlobalSpellbook.h"
#include "DataManagement/ItemDatabase.h"
#include "Config/GeneralConfig.h"
#include "SubSystems/PlayerInput.h"

class MonsterSpawner;

class GameRunningState : public GameStateImpl
{
    public:
        GameRunningState(const GeneralConfig& config);
        virtual ~GameRunningState();

		int InitializeState(SAS_System::Renderer& renderer, const SAS_System::Input& input);
		int UpdateState(int elapsedtime, SAS_System::Renderer& renderer, const SAS_System::Input& input);
		int TransitionIntoState(SAS_System::Renderer& renderer);
		int TransitionFromState(SAS_System::Renderer& renderer);
		int NextState() { return _nextstate; }

    private:
		void initializeECS(SAS_System::Renderer& renderer, const SAS_System::Input& input);

		GeneralConfig _generalconfig;
		int _nextstate;

		std::unique_ptr<PlayerInput> _inputhandler;
		uint64_t _player;

		// Game World Objects
        std::unique_ptr<GameWorld> _gameworld;
        std::unique_ptr<Camera>	_camera;

		// Game Data
		std::unique_ptr<GlobalSpellbook> _spellbook;

		// Game Object Manager
		//std::unique_ptr<ObjectManager>	objectmanager_;
		std::unique_ptr<ECSManager> _ecsmanager;

		// GUI Managers
		std::unique_ptr<SAS_GUI::GUIManager> _guimanager;

		std::unique_ptr<Items::ItemDatabase> _itemdatabase;
};
