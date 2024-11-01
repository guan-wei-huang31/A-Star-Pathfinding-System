#pragma once
#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H
#include "mapping.h"        //Include mapping header file for struct Route and struct Point

#define MAX_WEIGHT 2000.0	// Maximum weight of cargo in kilograms
#define MAX_VOLUME 20.0     // Maximum volume of cargo in cubic meters

// Define a structure for a Truck
typedef struct Truck
{
	struct Route route;  // Truck route infomation
	double totalWeight;  // Total weight of cargo loaded
	double totalVolume;  // Total volume of cargo loaded
	double loadedPersentage;
	char routeSymbol;    // Symbol representing the truck and route color
}Truck;

// Define a structure for a Shipment
typedef struct Shipment
{
	struct Point point;
	double weight;		// Weight of the individual shipment
	double boxSize;     // Size of the box (e.g., volume or dimensions)
}Shipment;

// A algorithm
typedef struct Node 
{
	struct Node* parent;   // Store parent's information
	struct Point point;    // Store current position 
	int g;    // distance between the current node and the start node.
	int h;    // distance from the current node to the end node
	int f;    // f = g + h;
} Node;


#endif