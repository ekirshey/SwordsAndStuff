#ifndef GAMERUNNINGSTATE_H
#define GAMERUNNINGSTATE_H

#include <memory>
#include "../StateFramework/GameState.h"
#include "../../ECSFramework/ObjectManager.h"
#include "../../HUD/HUDManager.h"
#include "../../GameWorld/GameWorld.h"
#include "../../GameWorld/Camera.h"
#include "../../GUI/GUIManager.h"

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
        void HandleStateInput();
        void UpdateState(int elapsedtime);
        void TransitionFromState();

		// Game World Objects
        std::unique_ptr<GameWorld>		gameworld_;
        std::unique_ptr<Camera>			camera_;

		// Game Object Manager
		std::unique_ptr<ObjectManager>	objectmanager_;

		// GUI Managers
		std::unique_ptr<HUDManager>		hudmanager_;
		std::unique_ptr<GUIManager>		guimanager_;
};

#endif // GAMERUNNINGSTATE_H
