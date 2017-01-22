#include "DiamondSquare.h"
#include "MapMath.h"
#include <cmath>
#include <random>
#include <iostream>
#include <string>
#include <map>
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

	double averagecorners(std::vector<double>& map, int nw, int ne, int sw, int se) {
		return	(map[nw] +
				 map[ne] +
				 map[sw] +
				 map[se]) / 4;
	}

	double averagecoords(std::vector<double>& map, Coord a, Coord b, Coord c, Coord d, int width) {
		return	(map[CoordsToIdx(a.x, a.y, width)] +
				 map[CoordsToIdx(b.x, b.y, width)] +
				 map[CoordsToIdx(c.x, c.y, width)] +
				 map[CoordsToIdx(d.x, d.y, width)]) / 4;
	}

	double noise(std::vector<double>& map ,double scale, std::mt19937& rng) {
		randomdist dist(0, 1);
		double rand = dist(rng);
		double noise = rand * 2;
		//double max = (scale + scale) / (width + width) * 3;
		
		//float max = num / (float)(getSize().width + getSize().height) * 3;
		//return ((float)Math.random() - 0.5f) * max;
		return ((rand - 0.5) * scale);
	}

	void calculateSquare(std::vector<double>& map, int x, int y, int center, int mapwidth, double scale, std::mt19937& rng) {
		Coord top{ x, y - center };
		Coord bottom{ x, y + center };
		Coord left{ x - center, y };
		Coord right{ x + center, y };
		if (x == 0) {
			left.x = mapwidth - 1 - center;
		}
		if (x == mapwidth - 1) {
			right.x = 0 + center;
		}
		if (y == 0) {
			top.y = mapwidth - 1 - center;
		}
		if (y == mapwidth - 1) {
			bottom.y = 0 + center;
		}
		map[CoordsToIdx(x, y, mapwidth)] = averagecoords(map, top, bottom, left, right, mapwidth) + noise(map, scale, rng);
	}

	void step(std::vector<double>& square, int ogwidth, int width, double scale, std::mt19937& rng) {
		if ( (width*width) <= 4) {
			return;
		}

		int center = width / 2;
		// Add Diamonds
		for (int i = center; i < ogwidth; i += width-1) {
			for (int j = center; j < ogwidth; j += width-1) {
				square[CoordsToIdx(i, j, ogwidth)] = averagecorners(square,
					CoordsToIdx(i - center, j - center, ogwidth),
					CoordsToIdx(i + center, j - center, ogwidth),
					CoordsToIdx(i - center, j + center, ogwidth),
					CoordsToIdx(i + center, j + center, ogwidth)
				) + noise(square, scale, rng);
			}
		}

		// Add Squares
		for (int i = center; i < ogwidth; i += width-1) {
			for (int j = center; j < ogwidth; j += width-1) {
				calculateSquare(square, i - center, j, center, ogwidth, scale, rng);
				calculateSquare(square, i + center, j, center, ogwidth, scale, rng);
				calculateSquare(square, i, j - center, center, ogwidth, scale, rng);
				calculateSquare(square, i, j + center, center, ogwidth, scale, rng);
			}
		}


		step(square, ogwidth, (width/2)+1, scale*0.5, rng);

	}

	void MovingAverageSmooth(std::vector<double>& map, int width) {
		for (int i = 1; i < width-1; i++) {
			for (int j = 1; j < width-1; j++) {
				map[CoordsToIdx(i, j, width)] = (map[CoordsToIdx(i - 1, j, width)] +
												 map[CoordsToIdx(i, j - 1, width)] +
												 map[CoordsToIdx(i + 1, j, width)] +
												 map[CoordsToIdx(i - 1, j+1, width)]
												) / 4;
			}
		}
	}


	std::vector<double> DiamondSquare(int n, double scale, int maxelevation) {
		// Initialize random generators
		std::mt19937 rng;
		rng.seed(std::random_device()());
		randomdist elevationdist(1, maxelevation);

		int sidelen = std::pow(2, n) + 1;
		int area = sidelen * sidelen;
		std::vector<double> heightmap(area);

		// First populate the four corners with random values
		double seed = elevationdist(rng);
		heightmap[CoordsToIdx(0, 0, sidelen)] = seed;
		heightmap[CoordsToIdx(sidelen - 1, 0, sidelen)] = seed;
		heightmap[CoordsToIdx(0, sidelen - 1, sidelen)] = seed;
		heightmap[CoordsToIdx(sidelen - 1, sidelen - 1, sidelen)] = seed;

		// First Diamond
		step(heightmap, sidelen, sidelen, maxelevation, rng);

		// Smooth
		MovingAverageSmooth(heightmap, sidelen);
		MovingAverageSmooth(heightmap, sidelen);
		//MovingAverageSmooth(heightmap, sidelen);

		return heightmap;
	}
}