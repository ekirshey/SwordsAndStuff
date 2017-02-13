#pragma once

#include <unordered_map>
#include <vector>
#include <utility>
#include <functional>
#include "Types/Stats.h"
#include "Components/StatsComponent.h"

class StatGenerator {
	public:
		StatGenerator(std::string formulafile);
		~StatGenerator() {}
		StatsComponent GenerateStats(MainStatMap mainstats);

	private:
		using DerivedPair = std::pair<DerivedStatType, StatValue>;
		// Map of Stattypes and functions where the function takes in the statpair to modify and a vector of statpairs used in the formula
		std::unordered_map<DerivedStatType, std::function<void(DerivedPair&, const std::vector<DerivedPair>&)>> _statformulas;
};
