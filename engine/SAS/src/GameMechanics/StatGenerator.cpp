#include "GameMechanics/StatGenerator.h"
#include "FileParser/cpptoml.h"

StatGenerator::StatGenerator(std::string formulafile) {

}


StatsComponent StatGenerator::GenerateStats(MainStatMap mainstats) {
	// Fill in the derived stats based on the main stats and then return
	DerivedStatMap derived;
	derived.insert({DerivedStatType::HEALTH, StatValue(100.0)});
	derived.insert({DerivedStatType::MANA, StatValue(100.0)});

	return StatsComponent(mainstats, derived);
}