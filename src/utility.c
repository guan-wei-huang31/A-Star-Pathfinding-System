//****************************************************************************
//Author: Guan-Wei Huang (gwhuang24@gmail.com)
//Copyright (c) 2024 Guan-Wei Huang
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>    //malloc, free
#include <ctype.h>     //toupper
#include "math.h"
#include "stdbool.h"
#include "mapping.h"
#include "utility.h"
#include "dataStructure.h"

//** Clears any remaining characters in the input buffer.
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//** Add multi-route to a map using the indicated symbol.
struct Map addMultipleRoutes(struct Map* map, struct Route* routes, int numRoutes) {
    struct Map updatedMap = *map;
    for (int i = 0; i < numRoutes; i++) {
        updatedMap = addRoute(&updatedMap, &routes[i]);
    }
    return updatedMap;
}

//** Prompts the user for shipment information and populates the cargo struct.
int getUserInput(struct Shipment* cargo) {
    printf("Enter shipment weight, box size and destination (0 0 x to stop): ");
    int tempRow;
    char tempCol;
    int result1 = scanf("%lf %lf %d", &cargo->weight, &cargo->boxSize, &tempRow);
    int result2 = scanf(" %c", &tempCol);

    cargo->point = usermapToNum(tempRow, tempCol);

    if (!(tempRow >= 0)) {  // Ensure quit only if row is not number(0-24)
   
        // Check if the user wants to stop -> quit
        if (cargo->weight == 0 && cargo->boxSize == 0 && tolower(tempCol) == 'x') {
            return 0;
        }
    }

    if (result1 != 3) {
        clearInputBuffer();
        printf("Invalid input format.\n");
        return -1;
    }
    if (result2 != 1) {
        clearInputBuffer();
        printf("Invalid input format.\n");
        return -1;
    }
    clearInputBuffer();

    // Validate input; return -1 if invalid
    int invalidType = validUserInput(*cargo);
    if (invalidType != 0) {
        return -1;
    }
    return 1;
}
//** Process User Input
struct Point usermapToNum(int row, char col) {
    struct Point result = { 0 };
    result.row = row - 1;                      // Convert row to zero - based index
    result.col = (int)(toupper(col) - 'A');    // Convert column letter to index

    return result;
};

//** Validates user input for shipment details.
int validUserInput(struct Shipment cargo) {
    if (cargo.point.row < 0 || cargo.point.row >= 25 || cargo.point.col < 0 || cargo.point.col >= 25) {
        printf("Invalid destination\n");
        return 1;
    }
    if (cargo.boxSize != 0.5 && cargo.boxSize != 1 && cargo.boxSize != 2) {
        printf("Invalid size\n");
        return 2;
    }
    if (cargo.weight <= 0 || cargo.weight > 2000) {
        printf("Invalid weight (must be 1 - 2000 Kg).\n");
        return 3;
    }
    return 0;
}

//**Finds the most suitable truck for a given shipment based on route and load.
int findTruckForShipment(const struct Map map, struct Truck* trucks, const int numTrucks, const struct Shipment cargo) {
    struct Route finalPath = { {0}, 9999999, -1 };   // Initialize with a very high path length
    int shortestTruckIndex = -1;

    // Iterate over each truck to find the one with sufficient capacity and the shortest path
    for (int j = 0; j < numTrucks; j++) {
        double checkWeight = trucks[j].totalWeight + cargo.weight;
        double checkVolume = trucks[j].totalVolume + cargo.boxSize;

        // Evaluate each point in the truck's route to find the shortest diversion to the shipment
        if (checkWeight <= MAX_WEIGHT && checkVolume <= MAX_VOLUME) {
            for (int i = 0; i < trucks[j].route.numPoints; i++) {
                struct Route tempPath = aStarPath(&map, trucks[j].route.points[i], cargo.point, trucks[j].route.routeSymbol);

                // Update finalPath if this route is shorter or has a lower load percentage
                if (tempPath.numPoints < finalPath.numPoints ||
                    (tempPath.numPoints == finalPath.numPoints && trucks[j].loadedPercentage < trucks[shortestTruckIndex].loadedPercentage)) {
                    finalPath = tempPath;
                    shortestTruckIndex = j;
                }
            }
        }
    }

    // Update the selected truck's diversion route and load information
    if (shortestTruckIndex != -1) {
        updateTruckDivert(&trucks[shortestTruckIndex], finalPath, cargo);
    }

    return shortestTruckIndex;
}

//** Calculates the shortest route between two points using the A* algorithm.
struct Route aStarPath(const struct Map* map, const struct Point start, const struct Point dest, int routeSymbol) {
    struct Route route = { {0}, 0, routeSymbol };        // Initialize route with zero points and route symbol
    struct Node* openList[MAP_ROWS * MAP_COLS];          // Open list to store nodes to be evaluated
    bool closedList[MAP_ROWS][MAP_COLS] = { false };     // Closed list to track visited nodes

    int openCount = 0;

    // Initialize the starting node and add it to the open list
    struct Node* startNode = (struct Node*)malloc(sizeof(struct Node));
    startNode->point = start;
    startNode->g = 0;
    startNode->h = distance(&start, &dest);
    startNode->f = startNode->g + startNode->h;
    startNode->parent = NULL;
    openList[openCount++] = startNode;

    // Main loop: Continue until the open list is empty
    while (openCount > 0) {

        // Find the node with the lowest f-cost in the open list
        int lowestIndex = 0;
        for (int i = 1; i < openCount; i++) {
            if (openList[i]->f < openList[lowestIndex]->f) {
                lowestIndex = i;
            }
        }

        struct Node* current = openList[lowestIndex];

        // Remove the node with the lowest f-cost from the open list
        for (int i = lowestIndex; i < openCount - 1; i++) {
            openList[i] = openList[i + 1];
        }
        openCount--;

        // Check if the destination is reached
        if (eqPt(current->point, dest)) {
            // Reconstruct the path by following parent pointers
            struct Node* pathNode = current;
            while (pathNode != NULL) {
                addPointToRoute(&route, pathNode->point.row, pathNode->point.col);
                pathNode = pathNode->parent;
            }

            // Reverse the route to get the correct order from start to destination
            for (int i = 0; i < route.numPoints / 2; i++) {
                struct Point temp = route.points[i];
                route.points[i] = route.points[route.numPoints - 1 - i];
                route.points[route.numPoints - 1 - i] = temp;
            }

            // Free any remaining nodes in the open list
            for (int i = 0; i < openCount; i++) {
                free(openList[i]);
            }
            free(current);  // Free the current node
            return route;   // Return the final path
        }

        // Mark the current node as visited by adding it to the closed list
        closedList[current->point.row][current->point.col] = true;

        // Get neighboring points and evaluate them
        struct Route neighbors = getPossibleMoves(map, current->point, dest, current->parent ? current->parent->point : (struct Point) { -1, -1 });
        for (int i = 0; i < neighbors.numPoints; i++) {
            struct Point neighborPos = neighbors.points[i];

            // Skip neighbors that are already visited
            if (closedList[neighborPos.row][neighborPos.col]) continue;

            // Calculate costs for the neighbor node
            int gCost = current->g + 1;
            double hCost = distance(&neighborPos, &dest);
            double fCost = gCost + hCost;

            bool skip = false;

            // Check if the neighbor is already in the open list with a lower f-cost
            for (int j = 0; j < openCount; j++) {
                if (openList[j]->point.row == neighborPos.row &&
                    openList[j]->point.col == neighborPos.col &&
                    openList[j]->f <= fCost) {
                    skip = true;
                    break;
                }
            }

            // If the neighbor is not in the open list with a better path, add it
            if (!skip && openCount < MAP_ROWS * MAP_COLS) {
                struct Node* neighborNode = (struct Node*)malloc(sizeof(struct Node));
                neighborNode->point = neighborPos;
                neighborNode->g = gCost;
                neighborNode->h = hCost;
                neighborNode->f = fCost;
                neighborNode->parent = current;
                openList[openCount++] = neighborNode;
            }
        }
    }

    // Free any remaining nodes in the open list if no path was found
    for (int i = 0; i < openCount; i++) {
        free(openList[i]);
    }

    // Indicate failure to find a path by setting numPoints to -1
    route.numPoints = -1;
    return route;
}

//** Updates the truck’s diversion route and load status after adding a shipment.
void updateTruckDivert(struct Truck* truck, const struct Route diversionRoute, const struct Shipment cargo) {
    if (truck != NULL && diversionRoute.points[diversionRoute.numPoints - 1].col == cargo.point.col && diversionRoute.points[diversionRoute.numPoints - 1].row == cargo.point.row) {
        truck->shortestDivert = diversionRoute;
        truck->totalVolume += cargo.boxSize;
        truck->totalWeight += cargo.weight;
        truck->loadedPercentage = fmax((truck->totalVolume / MAX_VOLUME) * 100, (truck->totalWeight / MAX_WEIGHT) * 100);
    }
}

//** Displays the diversion route for the truck, including any alternative routes.
void displayDivert(struct Route finalPath) {
    if (finalPath.numPoints == 2) {
        printf("no diversion");
    }
    else {
        printf("divert:");
        for (int i = 0; i < finalPath.numPoints; i++) {
            if (i > 0) printf(",");
            printf(" %d%c", finalPath.points[i].row + 1, toupper('A' + finalPath.points[i].col));
        }
    }
    printf("\n");
}

