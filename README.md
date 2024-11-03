# **A-Star-Pathfinding-System**

## **Project Overview**
This project simulates a delivery truck routing system for a local delivery company operating in a 25x25 grid city. The company uses three trucks, each assigned to specific routes (blue, yellow, and green) to efficiently deliver packages to designated buildings.  
The system provides truck routing, route selection, cargo tracking, and dynamic pathfinding using the A* algorithm for shortest path calculations.

---

## **📦Features**
- **Dynamic Route Optimization:** Uses the A* algorithm to dynamically calculate the shortest diversion paths based on cargo destination, ensuring efficient delivery.
- **Multi-Route Management:** Supports multiple pre-defined routes (Blue, Green, Yellow) for different trucks, enabling adaptable transport logistics.
- **Cargo and Truck Management:** Monitors truck capacity in real-time, including weight and volume checks, to ensure optimal load distribution.
- **User-Friendly Interaction:** Interactive user input allows operators to specify shipment details (weight, volume, and destination) and receive immediate routing suggestions.

---

## **📂Hierarchical file system**
```
fall24-sft221-nff-d/  
│                          
├── src/                             
│   ├── dataStructure.h                  // Data structure definitions
│   ├── main.c                           // Main program logic
│   ├── mapping.c                        // Mapping and route functions
│   ├── mapping.h                        // Mapping function declarations
│   ├── utility.c                        // Utility functions 
│   └── utility.h                        // Utility function declarations 
├── .gitignore                           
└── README.md                            

```
 
## **🚀Key Algorithm Steps**
- **Map Population and Visualization**: 
  1. A pre-defined map grid representing possible routes and obstacles is initialized and populated with delivery routes.
  2. Visual representation of routes on a 2D grid, making it easy to verify and understand routes.
- **Cargo Input and Validation**: 
  1. Accepts user input for cargo details (weight, volume, destination).
  2. Validates cargo attributes against maximum allowable weight and volume, as well as destination constraints.
- **Route Calculation and Optimization (A Algorithm)**: 
  1. Uses the A* pathfinding algorithm to calculate the shortest route or diversion for each truck, bypassing obstacles.
  2. Calculates Euclidean distance to provide efficient pathfinding based on real-world scenarios.
- **Truck Assignment and Load Management**: 
  1. Dynamically assigns the most suitable truck based on the load and the shortest path to the destination.
  2. Updates truck's load information, including total weight, volume, and utilized capacity, to prevent overloads.

---

## **🖨️Sample Output**
- 25x25 grid map (All trucks start at (1,A)):
  1. **X**: Building (Prohibited area, trucks cannot pass)
  2. **B**: Blue truck route
  3. **G**: Green truck route
  4. **Y**: Yellow truck route
  5. **+**: Overlap of all routes (Blue, Green, and Yellow)
  6. **.**: Overlap of Blue and Green routes
  7. **Space**: Road
    ```
        ABCDEFGHIJKLMNOPQRSTUVWXY
        -------------------------
      1|+   XX     GGGGGGGGG
      2|+XX XX XX  G    XX GXX
      3|+XX XX XX XGXX  XX GXX
      4|+          G       G
      5|++++......GG       G
      6|   Y     B         G
      7|XX YXX XXB     X XXG
      8|XX YXX X BXXX  X  XG  XXX
      9|   Y   X BXXX  X  XG  XXX
     10| YYY     B         GGGGGG
     11| Y       BB
     12|XYXXX     BXXXXXX XXX XXX
     13|XY    XXXXBXXXXXX XXX XXX
     14|XYXXX XXXXBXXXXXX XXX XXX
     15|XYXXX     BXXXXXX XXX XXX
     16|XY    XXX BXXXXXX XXX XXX
     17| Y    XXX B
     18| Y    XXX BBBBBBBBBBBBBBB
     19| Y    XXX    XXXXXXXXXXXX
     20| YYYYYYYYYYYYYYYYYYYYYYYY
     21|
     22| XXXXXXX  XX XX XXXX
     23| XXXXXXX  XX XX XXXX XXXX
     24| XXXXXXX  XX XX      XXXX
     25| XXXXXXX  XX XX
    ```
	
- **Input/output sample**:
  1. **Input**: Weight 20, Box size 5, destination 28x  
     - **Output**: Invalid destination (destination is out side of the 25x25 map)  
  2. **Input**: Weight 20, Box size 4, destination 12L  
     - **Output**: Invalid size (Box size must be 0.5, 1, 2 cubic meters)  
  3. **Input**: Weight 2100, Box size 2, destination 12L  
	 - **Output**: Invalid weight (must be 1 - 2000 Kg).  
  4. **Input**: Weight 20, Box size 2, destination 12L  
     - **Output**: Ship on BLUE LINE, no diversion (just next to the Blue route at 12K)  
  5. **Input**: Weight 1900, Box size 1, destination 8Y
     - **Output**: Ship on GREEN LINE, divert: 7T, 7U, 7V, 7W, 7X, 7Y, 8Y   (Shortest path on Green route start at 7T point)  
  6. **Input**: Weight 1900, Box size 1, destination 8Y
     - **Output**: Ship on Blue LINE, divert: 18V, 17V, ...  (Green truck is fully loaded with 1900 kg, so the second closest route is chosen)
  7. **Input**: 0 0 x
     - **Output**: End the program.
	```
    =================
    Seneca Polytechnic Deliveries:
    =================
    Enter shipment weight, box size and destination (0 0 x to stop): 20 5 28x
    Invalid destination
    Enter shipment weight, box size and destination (0 0 x to stop): 20 4 12L
    Invalid size
    Enter shipment weight, box size and destination (0 0 x to stop): 2100 2 12L
    Invalid weight (must be 1 - 2000 Kg).
    Enter shipment weight, box size and destination (0 0 x to stop): 20 2 12L
    Ship on BLUE LINE, no diversion
    Enter shipment weight, box size and destination (0 0 x to stop): 1900 1 8Y
    Ship on GREEN LINE, divert: 7T, 7U, 7V, 7W, 7X, 7Y, 8Y
    Enter shipment weight, box size and destination (0 0 x to stop): 1900 1 8Y
    Ship on BLUE LINE, divert: 18V, 17V, 16V, 15V, 14V, 13V, 12V, 11V, 10V, 9V, 8V, 7V, 7W, 7X, 7Y, 8Y
    Enter shipment weight, box size and destination (0 0 x to stop): 0 0 x
    ```

---

## **⚙️Usage**
1. **Clone the Repository**:
   - Clone the repository to your local machine:
   ```
   git clone https://github.com/guan-wei-huang31/A-Star-Pathfinding-System.git
   ```
2. **Compile the Code**:
   - Navigate to the SourceCode directory and compile the code:
3. **Run the Program**:
   - Run the executable to start the delivery system simulation.
4. **Input Orders**:
   - Input the shipment details (weight, size, destination) as prompted by the program to assign packages to trucks based on route efficiency and capacity.
5. **Output**:
   - The program will display the assigned truck, delivery route, and any necessary diversion paths.

---

## **Key Technical Concepts**
- **A star Algorithm**: Calculates the shortest path by minimizing cost f = g + h, where g is the movement cost from the start point and h is the heuristic estimate to the destination.
- **Euclidean Distance Calculation**: Used to optimize pathfinding accuracy in real-world applications.
- **Struct-based Management**: Organizes complex data structures for trucks, shipments, and map routes, making it easier to handle multiple entities and routes.

---
## **Future Enhancements**
- **Enhanced Route Mapping:** Allow dynamic addition of new routes based on changing map conditions.
- **Advanced Load Balancing:** Implement predictive load balancing across trucks based on expected delivery demand.
- **Graphical User Interface:** Provide a GUI for interactive route visualization and management.

---

### **📬Contact**
For questions or suggestions, feel free to contact:   
Email: ghuang24@gmail.com  


### **Conclusion**
This project showcases an efficient routing and delivery system leveraging the A* pathfinding algorithm, dynamic route management, and capacity tracking to meet logistical demands in a structured urban grid environment.