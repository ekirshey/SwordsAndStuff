#pragma once
#include "E:\GitHub\SwordsAndStuff\include\GameStates\StateFramework\GameState.h"

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
};

