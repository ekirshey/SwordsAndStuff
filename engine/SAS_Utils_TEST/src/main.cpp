#include "MapMath.h"
#include "HeightMapGenerator.h"
#include "DiamondSquare.h"
#include <iostream>


int main() {

	auto hm = SAS_Utils::DiamondSquare(8, 10.0, 100);

	SAS_Utils::WriteASCIIMapFile(hm,257 , "out.txt");

	system("PAUSE");
	return 0;
}