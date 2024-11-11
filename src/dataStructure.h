//****************************************************************************
//Author: Guan-Wei Huang (gwhuang24@gmail.com)
//Copyright (c) 2024 Guan-Wei Huang
//*****************************************************************************
#pragma once
#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H
#include "mapping.h"        //Include mapping header file for struct Route and struct Point

#define MAX_WEIGHT 2000.0	// Maximum weight of cargo in kilograms
#define MAX_VOLUME 20.0     // Maximum volume of cargo in cubic meters
#define NUM_ROUTES 3        // Total number of routes available for trucks

/**
 * Structure representing a truck and its route information.
 * @member route - the main route assigned to the truck
 * @member shortestDivert - the shortest diversion route for the truck
 * @member totalWeight - current total weight of cargo loaded on the truck
 * @member totalVolume - current total volume of cargo loaded on the truck
 * @member loadedPercentage - percentage of truck's maximum capacity utilized
 */
struct Truck
{
	struct Route route;            // Truck's assigned route information
	struct Route shortestDivert;   // Shortest diversion path for current shipment
	double totalWeight;            // Total weight of cargo on truck
	double totalVolume;            // Total volume of cargo on truck
	double loadedPercentage;        // Percentage of max capacity utilized
};

/**
 * Structure representing a shipment's destination and details.
 * @member point - destination point for the shipment
 * @member weight - weight of the shipment in kilograms
 * @member boxSize - size of the shipment box (volume or dimensions)
 */
struct Shipment
{
	struct Point point; // Destination point for the shipment
	double weight;		// Weight of the shipment
	double boxSize;     // Box size or volume of the shipment
};

/**
 * Structure representing a node in the A* algorithm.
 * @member parent - pointer to the parent node in the path
 * @member point - current point represented by this node
 * @member g - cost from the start point to this node
 * @member h - heuristic estimate cost to the destination
 * @member f - total cost (f = g + h), used for node comparison in A* algorithm
 */
struct Node {
	struct Node* parent;       // Parent node in the path
	struct Point point;        // Current point in the map
	int g;                     // Cost from start to this node
	double h;                  // Heuristic cost to destination
	double f;                  // Total cost (f = g + h)
};

#endif