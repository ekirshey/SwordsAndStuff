#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include <memory>
#include "../StateFramework/GameState.h"
#include "../../ECSFramework/ECSManager.h"
#include "../../GUI/GUIManager.h"

class MainMenuState : public GameState
{
    public:
		MainMenuState(bool persistent);
        virtual ~MainMenuState();

    private:
        // Removed an exit state cause i dont think it is necessary, just set to exit at end of transition
        void TransitionIntoState();
        void InitializeState();
        void UpdateState(int elapsedtime);
        void TransitionFromState();

		std::unique_ptr<GUIManager> guimanager_;
};

#endif // MAINMENUSTATE_H
