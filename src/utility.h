//****************************************************************************
//Author: Guan-Wei Huang (gwhuang24@gmail.com)
//Copyright (c) 2024 Guan-Wei Huang
//*****************************************************************************
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
 * Converts user-provided row and column input to a zero-based index format for map coordinates.
 * @param row - The row number provided by the user (1-based index).
 * @param col - The column letter provided by the user (A-Z or a-z).
 * @returns A Point struct with zero-based row and column indices.
 *          The row is calculated as (row - 1), and the column is calculated as (toupper(col) - 'A').
 */
struct Point usermapToNum(int row, char col);

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
* @param diversionRoute - Route struct representing the diversion path
* @param cargo - Shipment struct containing the new shipment details
*/
void updateTruckDivert(struct Truck* truck, const struct Route diversionRoute, const struct Shipment cargo);

/**
* Displays the diversion route for the truck, including any alternative routes.
* @param finalPath - Route struct containing the final path for the truck
*/
void displayDivert(struct Route finalPath);
#endif