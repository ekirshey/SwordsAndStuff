#include "MapMath.h"
#include "HeightMapGenerator.h"
#include "DiamondSquare.h"
#include <iostream>


int main() {

	auto hm = SAS_Utils::DiamondSquare(3, 10);

	//SAS_Utils::DisplayASCIIMap(hm, 9);

	system("PAUSE");
	return 0;
}