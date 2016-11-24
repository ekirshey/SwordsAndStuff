#pragma once
#include <vector>

namespace SAS_Utils{
	int CoordsToIdx(int x, int y, int width);

	// Debug
	void DisplayASCIIMap(const std::vector<double> map, int width);
	void DisplayOffsetASCIIMap(const std::vector<double> map, int x, int y, int ogwidth, int width);
	void WriteASCIIMapFile(const std::vector<double> map, int width, std::string file);
}
