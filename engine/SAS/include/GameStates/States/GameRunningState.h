#pragma once

#include <memory>
#include "StateFramework/GameState.h"
#include "GameWorld/GameWorld.h"
#include "GameWorld/Camera.h"
#include "GUIManager.h"
#include "ECSFramework/ECSManager.h"
#include "GameMechanics/Spells/GlobalSpellbook.h"
#include "DataManagement/ItemDatabase.h"

#ifdef FOO
class MonsterSpawner;

class GameRunningState : public GameState
{
    public:
        GameRunningState(bool persistent);
        virtual ~GameRunningState();

    private:
        // Removed an exit state cause i dont think it is necessary, just set to exit at end of transition
        void TransitionIntoState();
        void InitializeState();
        void UpdateState(int elapsedtime);
        void TransitionFromState();
		void InitializeECS();

		// Game World Objects
        std::unique_ptr<GameWorld>		gameworld_;
        std::unique_ptr<Camera>			camera_;

		// Game Data
		std::unique_ptr<GlobalSpellbook> spellbook_;

		// Game Object Manager
		//std::unique_ptr<ObjectManager>	objectmanager_;
		std::unique_ptr<ECSManager> ecsmanager_;

		// GUI Managers
		//std::unique_ptr<HUDManager>		hudmanager_;
		std::unique_ptr<SAS_GUI::GUIManager>		guimanager_;

		std::unique_ptr<Items::ItemDatabase> itemdatabase_;
};
#endif
