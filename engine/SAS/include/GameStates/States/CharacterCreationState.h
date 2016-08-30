#pragma once
#include <memory>
#include "../StateFramework/GameState.h"
#include "GUIManager.h"
#include "../../Components/DescriptionComponent.h"

class CharacterCreationState : public GameState
{
public:
	CharacterCreationState(bool persistent);
	~CharacterCreationState();


private:
	void InitializeState();
	void UpdateState(int elapsedtime);

	void TransitionIntoState();
	void TransitionFromState();

	std::unique_ptr<SAS_GUI::GUIManager> guimanager_;
	
	// Character Components
	DescriptionComponent characterDescription;

};

