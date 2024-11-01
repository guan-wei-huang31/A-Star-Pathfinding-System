#pragma once
#ifndef UTILITY_H
#define UTILITY_H

/**
* Add multi-route to a map using the indicated symbol.
* @param map - map to add route to
* @param routes - the routes to add to the map
* @returns a copy of the original map with the route added to it
*/
struct Map addMultipleRoutes(struct Map* map, struct Route* routes, int numRoutes);
int getUserInput(struct Shipment* cargo);
int validUserInput(struct Shipment cargo);
int findTruckForShipment(struct Map map, struct Truck* trucks, int numTrucks, struct Shipment cargo);
void convertAlphabetToNumber(struct Shipment* cargo, char* col);
void validPossibleMoves(struct Route* possible, struct Point p1, double currentDistance);
#endif