#ifndef GAMERUNNINGSTATE_H
#define GAMERUNNINGSTATE_H

#include <memory>
#include "../StateFramework/GameState.h"
#include "../../HUD/HUDManager.h"
#include "../../GameWorld/GameWorld.h"
#include "../../GameWorld/Camera.h"
#include "../../GUI/GUIManager.h"
#include "../../ECSFramework/ECSManager.h"
#include "../../GameMechanics/Spells/GlobalSpellbook.h"
#include "../../DataManagement/ItemDatabase.h"

class MonsterSpawner;

class GameRunningState : public GameState
{
    public:
        GameRunningState();
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
		std::unique_ptr<GUIManager>		guimanager_;

		std::unique_ptr<Items::ItemDatabase> itemdatabase_;
};

#endif // GAMERUNNINGSTATE_H
