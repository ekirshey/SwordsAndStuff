#pragma once
#include <string>
#include "Types/Stats.h"

/* This info will be built in the character creation state
	and then used to populate the ECS in the Game Running State
*/
struct PlayerInfo {
	std::string name;
	MainStatMap mainstats;

	// Defaults for a new player
	PlayerInfo() {
		mainstats[MainStatType::STRENGTH] = 10;
		mainstats[MainStatType::INTELLIGENCE] = 10;
	}
};
