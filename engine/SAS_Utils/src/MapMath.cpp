#include "MapMath.h"
#include <string>
#include <fstream>
#include <iostream>

namespace SAS_Utils {
	int CoordsToIdx(int x, int y, int width) {
		return  x + (width*y);
	}

	void DisplayASCIIMap(const std::vector<double> map, int width) {
		for (auto j = 0; j < map.size(); j++) {
			if ( (j> 0) && (j % width) == 0)
				std::cout << std::endl;
			std::cout << std::fixed << " " << map[j];
			if (map[j] >= 10)
				std::cout << "  ";
			else
				std::cout << "   ";
		}
		std::cout << std::endl;
	}

	void WriteASCIIMapFile(const std::vector<double> map, int width, std::string file) {
		std::ofstream outfile;
		outfile.open(file);

		for (auto j = 0; j < map.size(); j++) {
			if (j > 0)
				outfile << ",";
			if ((j > 0) && (j % width) == 0)
				outfile << std::endl;
			outfile << map[j];
		}

		outfile.close();
	}

	void DisplayOffsetASCIIMap(const std::vector<double> map, int x, int y, int ogwidth, int width) {
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