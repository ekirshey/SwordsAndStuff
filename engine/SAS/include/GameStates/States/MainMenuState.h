#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include <memory>
#include "GameState.h"
#include "ECSManager.h"
#include "GUIManager.h"

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

		std::unique_ptr<SAS_GUI::GUIManager> guimanager_;
};

#endif // MAINMENUSTATE_H
