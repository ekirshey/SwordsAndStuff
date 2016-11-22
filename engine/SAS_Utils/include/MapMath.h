#pragma once
#include <vector>

namespace SAS_Utils{
	int CoordsToIdx(int x, int y, int width);

	// Debug
	void DisplayASCIIMap(const std::vector<int> map, int width);
	void DisplayOffsetASCIIMap(const std::vector<int> map, int x, int y, int ogwidth, int width);
}
