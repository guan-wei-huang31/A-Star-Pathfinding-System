# **Delivery Truck Routing System**

## **Project Overview**
This project simulates a delivery truck routing system for a local delivery company operating in a 25x25 grid city. The company uses three trucks, each assigned to specific routes (blue, yellow, and green) to efficiently deliver packages to designated buildings.

---

## **📦Features**
- **Route Management:**
  1. Trucks follow pre-defined routes, but can divert slightly to deliver packages.
  2. A* algorithm is used to calculate the shortest path when a truck needs to deviate from its route.
- **Truck Capacity:**
  1. Each truck can carry up to 2000 kg or 20 cubic meters of packages.
  2. Packages come in sizes of 0.5, 1, or 2 cubic meters.
- **Delivery Assignment:**
  1. Packages are assigned based on truck availability and proximity to the destination.
  2. If trucks are at the same distance, the truck with more available space is chosen.
- **Handling Unreachable Destinations:**
  1. If a destination is unreachable (e.g., blocked by buildings), the program marks it as undeliverable by that truck.

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
- **Calculate Euclidean Distance**: At each point on a truck’s route, the Euclidean distance to the destination is calculated.
- **Pathfinding**: The A* algorithm determines the optimal diversion path, avoiding buildings.
- **Load Balancing**: Packages are added to trucks based on remaining weight/volume capacity.
- **Fallback Handling**: If no truck can deliver the package, it is stored for next-day delivery.

---

## **🖨️Sample Output**
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
   git clone https://github.com/ghuang33_seneca/fall24-sft221-nff-d.git
   ```
2. **Compile the Code**:
   - Navigate to the SourceCode directory and compile the code:
3. **Run the Program**:
   - Run the executable to start the delivery system simulation.
4. **Input Orders**:
   - Input the shipment details (weight, size, destination) as prompted by the program to assign packages to trucks based on route efficiency and capacity.
5. **Output**:
   - The program will display the assigned truck, delivery route, and any necessary diversion paths.

## **Technologies Used**
- **C Language**: Core programming language for implementing the delivery routing logic, data structures, and algorithms.
- **A Pathfinding Algorithm**: Used for calculating the shortest path, avoiding obstacles like buildings..

---

### **📬Contact**
For questions or suggestions, feel free to contact:   
Email: ghuang24@gmail.com  


### **Conclusion**
