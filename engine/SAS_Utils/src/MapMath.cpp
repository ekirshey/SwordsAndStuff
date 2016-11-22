#include "MapMath.h"
#include <iostream>

namespace SAS_Utils {
	int CoordsToIdx(int x, int y, int width) {
		return  x + (width*y);
	}

	void DisplayASCIIMap(const std::vector<int> map, int width) {
		for (auto j = 0; j < map.size(); j++) {
			if ( (j> 0) && (j % width) == 0)
				std::cout << std::endl;
			std::cout << " " << map[j];
			if (map[j] >= 10)
				std::cout << "  ";
			else
				std::cout << "   ";
		}
		std::cout << std::endl;
	}

	void DisplayOffsetASCIIMap(const std::vector<int> map, int x, int y, int ogwidth, int width) {
		int startingidx = CoordsToIdx(x, y, ogwidth);

		int count = 0;
		int i = startingidx;
		while (count < (width * width)) {
			if ( (count>0) && (count % width) == 0) {
				i += x;
				std::cout << std::endl;
			}
			std::cout << map[i++] << "   ";
			
			count++;
		}

	}
}