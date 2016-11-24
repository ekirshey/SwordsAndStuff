#pragma once
#include <vector>

namespace SAS_Utils {
	enum HeightMapAlgorithm {DIAMONDSQUARE};

	std::vector<double> GenerateHeightMap(HeightMapAlgorithm type, int n);
}

