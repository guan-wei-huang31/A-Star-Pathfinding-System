//****************************************************************************
//Author: Guan-Wei Huang (gwhuang24@gmail.com)
//Copyright (c) 2024 Guan-Wei Huang
//*****************************************************************************

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include "mapping.h"
#include "dataStructure.h"
#include "utility.h"

int main(void)
{
	// Initialize base map and populate it with predefined routes
	struct Map baseMap = populateMap();

	// Define and add multiple routes to the base map
	struct Route routes[] = { getBlueRoute(), getGreenRoute(), getYellowRoute() };
	struct Map finalMap = addMultipleRoutes(&baseMap, routes, NUM_ROUTES);

	// Print the map with all routes for verification
	printMap(&finalMap, 1, 1);

	// Initialize shipment and truck information
	struct Shipment cargo = { 0 };
	struct Truck truckBlue = { getBlueRoute(), {0}, 0, 0 , 0};
	struct Truck truckGreen = { getGreenRoute(), {0}, 0, 0, 0 };
	struct Truck truckYellow = { getYellowRoute(), {0}, 0, 0, 0 };
	struct Truck trucks[] = { truckBlue, truckGreen, truckYellow };

	// Display header for delivery information
	printf("\n");
	printf("=================\n"
		"Seneca Polytechnic Deliveries:\n"
		"=================\n");
	int getInputFlag = 1;

	// Main input loop: process user input for shipment and find an appropriate truck
	do {
		// Get user input for cargo details and validate input
		getInputFlag = getUserInput(&cargo);
		if (getInputFlag == 1) {

			// Find the most suitable truck for the shipment based on route and load
			int validTruckIndex = findTruckForShipment(baseMap, trucks, NUM_ROUTES, cargo);
			
			// Display the result based on the truck assigned
			switch (validTruckIndex) {
			case 0:
				printf("Ship on BLUE LINE, ");
				displayDivert(trucks[0].shortestDivert);
				break;
			case 1:
				printf("Ship on GREEN LINE, ");
				displayDivert(trucks[1].shortestDivert);
				break;
			case 2:
				printf("Ship on YELLOW LINE, ");
				displayDivert(trucks[2].shortestDivert);
				break;
			default:
				printf("There is no avaliable truck.");
				break;
			}
		}
	} while (getInputFlag != 0);

	return 0;
}