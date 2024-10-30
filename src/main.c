#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "mapping.h"
#include "dataStructure.h"

int main(void)
{
	struct Map baseMap = populateMap();
	struct Route blueRoute = getBlueRoute();
	struct Route greenRoute = getGreenRoute();
	struct Route yellowRoute = getYellowRoute();
	struct Route routes[] = { blueRoute, greenRoute, yellowRoute };
	struct Map finalMap = addMultipleRoutes(&baseMap, routes, 3);

	printMap(&finalMap, 1, 1);

	struct Truck truckBlue = { blueRoute, 0.0, 0.0, 0.0, 'B' };
	struct Truck truckGreen = { greenRoute, 0.0, 0.0, 0.0, 'G' };
	struct Truck truckYellow = { yellowRoute, 0.0, 0.0, 0.0, 'Y' };
	struct Truck trucks[] = { truckBlue, truckGreen, truckYellow };

	struct Shipment cargo = { 0 };

	return 0;
}