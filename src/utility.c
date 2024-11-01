#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include "mapping.h"
#include "utility.h"
#include "dataStructure.h"
#include "math.h"
#include "stdbool.h"

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

struct Map addMultipleRoutes(struct Map* map, struct Route* routes, int numRoutes) {
    struct Map updatedMap = *map;
    for (int i = 0; i < numRoutes; i++) {
        updatedMap = addRoute(&updatedMap, &routes[i]);
    }
    return updatedMap;
}

int getUserInput(struct Shipment* cargo) {

    printf("Enter shipment weight, box size and destination (0 0 x to stop): ");
    int tempRow;
    char tempCol;
    scanf("%lf %lf %d", &cargo->weight, &cargo->boxSize, &tempRow);
    scanf(" %c", &tempCol);
    cargo->point.row = tempRow - 1;
    clearInputBuffer();
    
    if (cargo->weight == 0 && cargo->boxSize == 0 && tolower(tempCol) == 'x') {
        return 0;
    }

    convertAlphabetToNumber(cargo,&tempCol);

    int invalidType = validUserInput(*cargo);
    switch (invalidType) {
    case 1:
        printf("Invalid destination\n");
        break;
    case 2:
        printf("Invalid size\n");
        break;
    case 3:
        printf("Invalid weight(must be 1 - 2000 Kg.\n");
        break;
    default:
        break;
    }
    return 1;
}

int validUserInput(struct Shipment cargo) {
    if (cargo.point.row < 0 || cargo.point.row > 25 || cargo.point.col < 0 || cargo.point.col > 25) {
        return 1;
    }
    if (cargo.boxSize != 0.5 && cargo.boxSize != 1 && cargo.boxSize != 2) {
        return 2;
    } 
    if (cargo.weight <= 0 || cargo.weight > 2000) {
        return 3;
    }
}

void convertAlphabetToNumber(struct Shipment* cargo, char* col) {
    cargo->point.col = (int)(toupper(*col) - 'A');
}

Node* create_node(Node* parent, struct Point pt) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    new_node->parent = parent;
    new_node->point = pt;
    new_node->g = 0;
    new_node->h = 0;
    new_node->f = 0;
    return new_node;
}

void add_to_open_list(Node** open_list, int* open_list_size, Node* node) {
    if (*open_list_size < 100) {
        open_list[*open_list_size] = node;
        (*open_list_size)++;
    }
    else {
        fprintf(stderr, "Open list overflow\n");
    }
}

void remove_from_open_list(Node** open_list, int* open_list_size, int index) {
    if (index < *open_list_size) {
        for (int i = index; i < *open_list_size - 1; i++) {
            open_list[i] = open_list[i + 1];
        }
        (*open_list_size)--;
    }
}

int get_lowest_f_index(Node** open_list, int open_list_size) {
    int lowest_index = 0;
    for (int i = 1; i < open_list_size; i++) {
        if (open_list[i]->f < open_list[lowest_index]->f) {
            lowest_index = i;
        }
    }
    return lowest_index;
}

bool is_within_map(struct Map* map, struct Point pt) {
    return (pt.row >= 0 && pt.row < map->numRows && pt.col >= 0 && pt.col < map->numCols);
}

bool is_walkable(struct Map* map, struct Point pt) {
    return map->squares[pt.row][pt.col] == 0;
}

bool is_in_closed_list(Node** closed_list, int closed_list_size, Node* node) {
    for (int i = 0; i < closed_list_size; i++) {
        if (closed_list[i]->point.row == node->point.row && closed_list[i]->point.col == node->point.col) {
            return true;
        }
    }
    return false;
}

struct Point* a_star(struct Map* map, struct Point start, struct Point dest, int* path_length) {
    Node* start_node = create_node(NULL, start);
    Node* dest_node = create_node(NULL, dest);

    Node* open_list[1000];
    int open_list_size = 0;
    Node* closed_list[1000];
    int closed_list_size = 0;

    add_to_open_list(open_list, &open_list_size, start_node);

    while (open_list_size > 0) {
        int current_index = get_lowest_f_index(open_list, open_list_size);
        Node* current_node = open_list[current_index];

        remove_from_open_list(open_list, &open_list_size, current_index);
        if (closed_list_size < 100) {
            closed_list[closed_list_size++] = current_node;
        }
        else {
            fprintf(stderr, "Closed list overflow\n");
            break;
        }

        if (current_node->point.row == dest_node->point.row &&
            current_node->point.col == dest_node->point.col) {

            *path_length = 0;
            Node* path_node = current_node;
            while (path_node != NULL) {
                (*path_length)++;
                path_node = path_node->parent;
            }

            struct Point* path = (struct Point*)malloc(*path_length * sizeof(struct Point));
            if (!path) {
                fprintf(stderr, "Memory allocation failed for path\n");
                exit(1);
            }
            path_node = current_node;
            for (int i = *path_length - 1; i >= 0; i--) {
                path[i] = path_node->point;
                path_node = path_node->parent;
            }

            free(dest_node);
            return path;
        }

        struct Point directions[8] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };
        for (int i = 0; i < 8; i++) {
            struct Point new_position = { current_node->point.row + directions[i].row, current_node->point.col + directions[i].col };

            if (!is_within_map(map, new_position) || !is_walkable(map, new_position)) continue;

            Node* child = create_node(current_node, new_position);

            if (is_in_closed_list(closed_list, closed_list_size, child)) {
                free(child);
                continue;
            }

            child->g = current_node->g + 1;
            child->h = (child->point.row - dest_node->point.row) * (child->point.row - dest_node->point.row) +
                (child->point.col - dest_node->point.col) * (child->point.col - dest_node->point.col);
            child->f = child->g + child->h;

            bool add_child = true;
            for (int j = 0; j < open_list_size; j++) {
                if (open_list[j]->point.row == child->point.row && open_list[j]->point.col == child->point.col &&
                    child->g > open_list[j]->g) {
                    add_child = false;
                    break;
                }
            }

            if (add_child) add_to_open_list(open_list, &open_list_size, child);
            else free(child);
        }
    }

    free(dest_node);
    return NULL;
}


int findTruckForShipment(struct Map map, struct Truck* trucks, int numTrucks, struct Shipment cargo) {
    struct Point strat = { 8, 11 };
    int path_length;
    struct Point* path = a_star(&map, strat, cargo.point, &path_length);
    if (path) {
        printf("Path found:\n");
        for (int i = 0; i < path_length; i++) {
            printf("(%d, %d) ", path[i].row, path[i].col);
        }
        free(path);
    }
    else {
        printf("No path found.\n");
    }

    return 1;  // жие\
}