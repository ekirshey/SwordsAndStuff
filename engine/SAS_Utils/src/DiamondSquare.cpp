#include "DiamondSquare.h"
#include "MapMath.h"
#include <cmath>
#include <random>
#include <iostream>
namespace SAS_Utils {
	using randomdist = std::uniform_int_distribution<std::mt19937::result_type>;
	struct Coord {
		int x; 
		int y;
		Coord(int x, int y)
			: x(x)
			, y(y)
		{

		}
	};

	int averagecorners(std::vector<int>& map, int nw, int ne, int sw, int se) {
		return	(map[nw] +
				 map[ne] +
				 map[sw] +
				 map[se]) / 4;
	}

	int averagecoords(std::vector<int>& map, Coord a, Coord b, Coord c, Coord d, int width) {
		return	(map[CoordsToIdx(a.x, a.y, width)] +
				 map[CoordsToIdx(b.x, b.y, width)] +
				 map[CoordsToIdx(c.x, c.y, width)] +
				 map[CoordsToIdx(d.x, d.y, width)]) / 4;
	}

	void calculateSquare(std::vector<int>& map, int x, int y, int center, int mapwidth, int scale, randomdist& dist, std::mt19937& rng) {
		Coord top{ x, y - center };
		Coord bottom{ x, y + center };
		Coord left{ x - center, y };
		Coord right{ x + center, y };
		if (x == 0) {
			left.x = mapwidth - 1;
		}
		if (x == mapwidth - 1) {
			right.x = 0;
		}
		if (y == 0) {
			top.y = mapwidth - 1;
		}
		if (y == mapwidth - 1) {
			bottom.y = 0;
		}

		map[CoordsToIdx(x, y, mapwidth)] = averagecoords(map, top, bottom, left, right, mapwidth) + dist(rng) * scale;
	}

	void step(std::vector<int>& square, int ogwidth, int width, int scale, randomdist& dist, std::mt19937& rng) {
		if ( (width*width) <= 4) {
			return;
		}
		std::vector<Coord> diamonds;

		int center = width / 2;

		// Add Diamonds
		for (int i = center; i < ogwidth; i += width-1) {
			for (int j = center; j < ogwidth; j += width-1) {
				square[CoordsToIdx(i, j, ogwidth)] = averagecorners(square,
																	CoordsToIdx(i-center, j-center, ogwidth),
																	CoordsToIdx(i+center, j-center, ogwidth),
																	CoordsToIdx(i-center, j+center, ogwidth),
																	CoordsToIdx(i+center, j+center, ogwidth)
																	) + dist(rng) * scale;
				diamonds.push_back(Coord{ i,j });
			}
		}

		// Add Squares
		for (auto& coord : diamonds) {
			calculateSquare(square, coord.x - center, coord.y, center, ogwidth, scale, dist, rng);
			calculateSquare(square, coord.x + center, coord.y, center, ogwidth, scale, dist, rng);
			calculateSquare(square, coord.x, coord.y - center, center, ogwidth, scale, dist, rng);
			calculateSquare(square, coord.x, coord.y + center, center, ogwidth, scale, dist, rng);
		}

		step(square, ogwidth, (width/2)+1, scale/2, dist, rng);

	}

	void step2(std::vector<int>& square, int ogwidth, int width, int xoffset, int yoffset,  randomdist& dist, std::mt19937& rng) {
		if ((width*width) <= 4) {
			return;
		}

		int center = std::floor(width / 2);
		int x_width = (center + xoffset);
		int y_width = (center + yoffset);

		// Add Diamond
		square[CoordsToIdx(x_width, y_width, ogwidth)] =  
			averagecorners( square, 
							CoordsToIdx(0 + xoffset, 0 + yoffset, ogwidth),
							CoordsToIdx((width-1) + xoffset, 0 + yoffset, ogwidth),
							CoordsToIdx(0 + xoffset, (width-1) + yoffset, ogwidth),
							CoordsToIdx((width-1) + xoffset, (width-1) + yoffset, ogwidth)
							) + dist(rng);

		// Add Squares
		square[CoordsToIdx(x_width, 0 + yoffset, ogwidth)] = 1;
		square[CoordsToIdx(0 + xoffset, y_width, ogwidth)] = 2;
		square[CoordsToIdx((width-1) +xoffset, y_width, ogwidth)] = 3;
		square[CoordsToIdx(x_width, (width-1) + yoffset, ogwidth)] = 4;

		DisplayASCIIMap(square, ogwidth);
		std::cout << std::endl;
		std::cout << std::endl;


		int new_width = center + 1;
		step2(square, ogwidth, new_width, xoffset, yoffset, dist, rng);
		step2(square, ogwidth, new_width, xoffset + center, yoffset, dist, rng);
		step2(square, ogwidth, new_width, xoffset, yoffset + center, dist, rng);
		step2(square, ogwidth, new_width, xoffset + center, yoffset + center, dist, rng);

	}

	std::vector<int> DiamondSquare(int n, int maxelevation) {
		// Initialize random generators
		std::mt19937 rng;
		rng.seed(std::random_device()());
		randomdist elevationdist(1, maxelevation);

		int sidelen = std::pow(2, n) + 1;
		int area = sidelen * sidelen;
		std::vector<int> heightmap(area);

		// First populate the four corners with random values
		heightmap[CoordsToIdx(0, 0, sidelen)] = elevationdist(rng);
		heightmap[CoordsToIdx(sidelen-1, 0, sidelen)] = elevationdist(rng);
		heightmap[CoordsToIdx(0, sidelen-1, sidelen)] = elevationdist(rng);
		heightmap[CoordsToIdx(sidelen-1, sidelen-1, sidelen)] = elevationdist(rng);

		// First Diamond
		step(heightmap, sidelen, sidelen, 10, elevationdist, rng);

		//DisplayASCIIMap(heightmap, sidelen);
		return heightmap;
	}
}