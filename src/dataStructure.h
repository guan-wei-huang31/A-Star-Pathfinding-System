#pragma once
#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H
#include "mapping.h"        //Include mapping header file for struct Route and struct Point

#define MAX_WEIGHT 2000.0	// Maximum weight of cargo in kilograms
#define MAX_VOLUME 20.0     // Maximum volume of cargo in cubic meters

// Define a structure for a Truck
struct Truck
{
	struct Route route;  // Truck route infomation
	double totalWeight;  // Total weight of cargo loaded
	double totalVolume;  // Total volume of cargo loaded
	double loadedPercentage; // Percentage of truck loaded
	char routeSymbol;    // Symbol representing the truck and route color
};

// Define a structure for a Shipment
struct Shipment
{
	double weight;		// Weight of the individual shipment
	double boxSize;     // Size of the box (e.g., volume or dimensions)
	struct Point destination; // Destination point
};

#endif
