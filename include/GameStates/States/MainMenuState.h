#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "../StateFramework/GameState.h"
#include "../../ECSFramework/ECSManager.h"

class MainMenuState : public GameState
{
    public:
        MainMenuState();
        virtual ~MainMenuState();

    private:
        // Removed an exit state cause i dont think it is necessary, just set to exit at end of transition
        void TransitionIntoState();
        void InitializeState();
        void UpdateState(int elapsedtime);
        void TransitionFromState();

        ECSManager ecsmanager_;
};

#endif // MAINMENUSTATE_H
