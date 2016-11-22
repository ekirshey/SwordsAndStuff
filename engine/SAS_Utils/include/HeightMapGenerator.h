#pragma once
#include <vector>

namespace SAS_Utils {
	enum HeightMapAlgorithm {DIAMONDSQUARE};

	std::vector<int> GenerateHeightMap(HeightMapAlgorithm type, int n);
}

