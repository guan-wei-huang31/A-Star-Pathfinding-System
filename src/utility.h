#pragma once
#ifndef UTILITY_H
#define UTILITY_H

/**
 * Clears any remaining characters in the input buffer.
 * This function discards any characters left in the standard input buffer,
 * typically used after `scanf` to prevent unwanted characters from interfering with further input.
 */
void clearInputBuffer();

/**
* Add multi-route to a map using the indicated symbol.
* @param map - map to add route to
* @param routes - the routes to add to the map
* @returns a copy of the original map with the route added to it
*/
struct Map addMultipleRoutes(struct Map* map, struct Route* routes, int numRoutes);

/**
* Prompts the user for shipment information and populates the cargo struct.
* @param cargo - pointer to the Shipment struct to store user input
* @returns 1 if valid input is received, 0 to stop, or -1 for invalid input
*/
int getUserInput(struct Shipment* cargo);

/**
* Validates user input for shipment details.
* @param cargo - Shipment struct containing user input
* @returns 0 if input is valid, or an error code for specific validation failures
*/
int validUserInput(struct Shipment cargo);

/**
* Finds the most suitable truck for a given shipment based on route and load.
* @param map - map to use for route calculation
* @param trucks - array of trucks to consider for the shipment
* @param numTrucks - number of trucks available
* @param cargo - Shipment struct containing the shipment details
* @returns the index of the most suitable truck, or -1 if no truck is available
*/
int findTruckForShipment(const struct Map map, struct Truck* trucks, const int numTrucks, const struct Shipment cargo);

/**
* Calculates the shortest route between two points using the A* algorithm.
* @param map - map containing route information
* @param start - starting point of the route
* @param dest - destination point of the route
* @param routeSymbol - symbol representing the route
* @returns a Route struct containing the calculated path
*/
struct Route aStarPath(const struct Map* map, const struct Point start, const struct Point dest, int routeSymbol);

/**
* Updates the truck¡¦s diversion route and load status after adding a shipment.
* @param truck - pointer to the Truck struct to update
* @param final - Route struct representing the diversion path
* @param cargo - Shipment struct containing the new shipment details
*/
void updateTruckDivert(struct Truck* truck, const struct Route final, const struct Shipment cargo);

/**
* Displays the diversion route for the truck, including any alternative routes.
* @param finalPath - Route struct containing the final path for the truck
*/
void displayDivert(struct Route finalPath);
#endif