#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include <memory>
#include "StateFramework/GameState.h"
#include "ECSFramework/ECSManager.h"
#include "GUIManager.h"
#include "Config/GeneralConfig.h"

class MainMenuState : public GameStateImpl
{
    public:
		MainMenuState(const GeneralConfig& config);
        virtual ~MainMenuState();

		int InitializeState(SAS_System::Renderer& renderer, const SAS_System::Input& input);
		int UpdateState(int elapsedtime, SAS_System::Renderer& renderer, const SAS_System::Input& input);
		int TransitionIntoState(SAS_System::Renderer& renderer);
		int TransitionFromState(SAS_System::Renderer& renderer);
		int NextState() { return _nextstate; }

	private:
		// Config Structs
		GeneralConfig _generalconfig;

		int _nextstate;
		bool _exit;
		SAS_GUI::GUIManager _guimanager;
};

#endif // MAINMENUSTATE_H
