#pragma once
#include <utility>

enum class MainStatType { STRENGTH, INTELLIGENCE };
enum class DerivedStatType{HEALTH, MANA};

struct StatValue {
	double maxstat;
	double currentstat;

	StatValue() : maxstat(0), currentstat(0) {}
	StatValue(double max)
		: maxstat(max)
		, currentstat(max)
	{

	}
};

using MainStatMap = std::unordered_map<MainStatType, StatValue>;
using DerivedStatMap = std::unordered_map<DerivedStatType, StatValue>;
