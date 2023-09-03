#include <iostream>
#include <string>
#include <limits>

#ifdef _WIN32
#include <windows.h> // For Windows
#else
#include <cstdlib>    // For Linux and other Unix-like systems
#endif

constexpr int NO_OF_MENUITEMS{4};  // No:of menu options
constexpr int  NO_OF_NODES{15};    // No:of nodes within the graph
constexpr int DEPTH{3};

void clearScreen() {
#ifdef _WIN32
    std::system("cls"); // Windows
#else
    std::system("clear"); // Linux and other Unix-like systems
#endif
}

void displayMap(){ // The map to be displayed. When the matrix representation of the graph is updated, update the below map to reflect those changes.
    clearScreen();
    std::string map = R"(            (1)Nilambur----(12km,22min,15rs)
               /                        \
        (7km,14min,10rs)                 \
             /                            \
          (2)Mampad---(9km,16min,12rs)    (3)Pookkottumpadam
           /                 \                /        \
          /                   \              /          \
    (9km,17min,10rs)           \   (12km,25min,15rs)   (8km,19min,10rs)----(4)Chokkad
         |                      \         /                                      |(8km,18min,10rs)
         |                       \       /                                       |
  (5)Edavanna--(12km,20min,15rs)-(6)Wandoor------(11km,23min,14rs)-----(7)Kalikavu
         |                        |                                               \(10km,19min,12rs)
         |                        |                                                \
    (13km,30min,17rs)       (13km,21min,17rs)   (8)Thuvvur-(9km,15min,10rs)--(9)Karuvarakundu
         |                        |            /                              /
         |                        |     (10km,20min,10rs)                    /
         |                        |         /                        (13km,22min,17rs)
 (10)Manjeri-(14km,25min,18rs)-(11)Pandikkad                               /
         /                         |        \                             /
    (12km,23min,15rs)              |         (9km,20min,10rs)------(12)Melattur
       /                   (15km,32min,20rs)                              \
  (13)Malappuram                   |                                 (26km,40min,15rs)
       \                           |                                         \
        (22km,40min,25rs)-----(14)Perinthalmanna------(30km,45min,55rs)--(15)Mannarkkadu)";
    std::cout << map << "\n\n";
}

void displayMenu(){
    std::cout << "(1) Find the shortest path\t\t(2) Find the minimum time path\n(3) Find the minimum cost path\t\t(4) Exit out of application\n\nEnter a menu option: ";
}

int getValidInputOption(int maxValue) { // maxValue is the maximum acceptable input value.
    int userInput{0};
    while (true) {
        std::cin >> userInput;

        if (userInput > 0 && userInput <= maxValue) {
            return userInput; // Return valid input
        } else {
            std::cout << "Invalid input. Please enter a valid number.\n";
            std::cin.clear();   // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore remaining characters
        }
    }
}

void waitForKeypress() {
    std::cout << "\nPress Enter to go back to home screen...";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

// Function to print the backTrackingArr in reverse order. backTrackingArr contains the details of the modified nodes and who modified them, which is used to find the path from source to destination.
void backTrack(int backTrackingArr[], int currentNode, int sourceNode){
    if(currentNode == sourceNode){
        // Base case: Reached the source node or an untouched node (infinity)
        std::cout << currentNode+1;
        return;
    }
    // Recursive case: Continue backtracking to the previous node
    backTrack(backTrackingArr, backTrackingArr[currentNode], sourceNode);
    std::cout << " -> " << currentNode+1;
}

void findShortestPath(int matrix[][NO_OF_NODES][DEPTH]){
    clearScreen();
    displayMap();
    std::cout << "Enter source city number: ";
    int source{0};
    source = getValidInputOption(NO_OF_NODES);
    std::cout << "Enter destination city number: ";
    int destination{0};
    destination = getValidInputOption(NO_OF_NODES);

    int minPathArr[NO_OF_NODES]{};
    int minTimeArr[NO_OF_NODES]{};
    int backTrackingArr[NO_OF_NODES]{};
    int visitedOrNotArr[NO_OF_NODES]{0};

    for(int i{0}; i < NO_OF_NODES; ++i){
        minPathArr[i] = std::numeric_limits<int>::max();
        minTimeArr[i] = std::numeric_limits<int>::max();
        backTrackingArr[i] = std::numeric_limits<int>::max();
        visitedOrNotArr[i] = 0;
    }

    minPathArr[source-1] = 0; //setting the source node distance to zero.
    minTimeArr[source-1] = 0; //setting the source node time taken to zero.

    int node{-1};
    int minimumDistance{0};
    while(visitedOrNotArr[destination-1] != 1){
        //find the node with the smallest distance from among the non visited nodes.
        minimumDistance = std::numeric_limits<int>::max();
        node = -1;
        for(int i{0}; i < NO_OF_NODES; ++i){
            if(visitedOrNotArr[i] == 0 && minPathArr[i] < minimumDistance){
                minimumDistance = minPathArr[i];
                node = i;
            }
        }

        for(int i{0}; i < NO_OF_NODES; ++i){
            if(matrix[node][i][0] != 0){
                if(matrix[node][i][0] + minPathArr[node] < minPathArr[i]){
                    minPathArr[i] = matrix[node][i][0] + minPathArr[node];
                    minTimeArr[i] = matrix[node][i][1] + minTimeArr[node];
                    backTrackingArr[i] = node;
                }
                //if there are multiple paths with the same distance to reach a specific node from the source, we chooses a path which takes minimum time to reach that specific node from the source.
                else if(matrix[node][i][0] + minPathArr[node] == minPathArr[i]){
                    if(matrix[node][i][1] + minTimeArr[node] < minTimeArr[i]){
                        minTimeArr[i] = matrix[node][i][1] + minTimeArr[node];
                        backTrackingArr[i] = node;
                    }
                }
            }
        }
        visitedOrNotArr[node] = 1;
    }
    //Output
    std::cout << "\nFor travelling from " << source << " to " << destination << ", it takes " << minPathArr[destination-1] << " KM and " << minTimeArr[destination-1] << " minutes.\nPath: ";
    backTrack(backTrackingArr, destination-1, source-1);
    std::cout << std::endl;
}

//Function for finding the minimum time path and minimum cost path using Dijkstra's algorithm
void findMinTimeOrCostPath(int matrix[][NO_OF_NODES][DEPTH], int index){ //index is used to fetch the time/cost value from the graph matrix.
    clearScreen();
    displayMap();
    std::cout << "Enter source city number: ";
    int source{0};
    source = getValidInputOption(NO_OF_NODES);
    std::cout << "Enter destination city number: ";
    int destination{0};
    destination = getValidInputOption(NO_OF_NODES);

    int minPathArr[NO_OF_NODES]{};
    int backTrackingArr[NO_OF_NODES]{};
    int visitedOrNotArr[NO_OF_NODES]{0};

    for(int i{0}; i < NO_OF_NODES; ++i){
        minPathArr[i] = std::numeric_limits<int>::max();
        backTrackingArr[i] = std::numeric_limits<int>::max();
        visitedOrNotArr[i] = 0;
    }

    minPathArr[source-1] = 0; //setting the source node time/cost value to zero.
    int node{-1};
    int minimumNodeValue{0};
    while(visitedOrNotArr[destination-1] != 1){
        //find the node with the smallest distance from among the non visited nodes.
        minimumNodeValue = std::numeric_limits<int>::max();
        node = -1;
        for(int i{0}; i < NO_OF_NODES; ++i){
            if(visitedOrNotArr[i] == 0 && minPathArr[i] < minimumNodeValue){
                minimumNodeValue = minPathArr[i];
                node = i;
            }
        }
        for(int i{0}; i < NO_OF_NODES; ++i){
            if(matrix[node][i][index] != 0){
                if(matrix[node][i][index] + minPathArr[node] < minPathArr[i]){
                    minPathArr[i] = matrix[node][i][index] + minPathArr[node];
                    backTrackingArr[i] = node;
                }

            }
        }
        visitedOrNotArr[node] = 1;
    }
    //Output
    std::cout << "\nFor travelling from " << source << " to " << destination << ", it takes " << minPathArr[destination-1] << ((index == 1)?" Minutes":" Rupees") << ".\nPath: ";
    backTrack(backTrackingArr, destination-1, source-1);
    std::cout << std::endl;
}

int main(){
    //Define the graph
    // int graph[NO_OF_NODES][NO_OF_NODES][DEPTH]{ // Testing graph.
    //     {{0,0,0},{6,7,4},{5,4,2},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
    //     {{6,7,4},{0,0,0},{0,0,0},{4,3,7},{5,6,3},{0,0,0},{0,0,0}},
    //     {{5,4,2},{0,0,0},{0,0,0},{7,3,4},{0,0,0},{4,4,4},{0,0,0}},
    //     {{0,0,0},{4,3,7},{7,3,4},{0,0,0},{0,0,0},{0,0,0},{4,2,6}},
    //     {{0,0,0},{5,6,3},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{2,5,7}},
    //     {{0,0,0},{0,0,0},{4,4,4},{0,0,0},{0,0,0},{0,0,0},{3,4,6}},
    //     {{0,0,0},{0,0,0},{0,0,0},{4,2,6},{2,5,7},{3,4,6},{0,0,0}}
    // };

    int graph[NO_OF_NODES][NO_OF_NODES][DEPTH]{
        {{0,0,0},{7,14,10},{12,22,15},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
        {{7,14,10},{0,0,0},{0,0,0},{0,0,0},{9,17,10},{9,16,12},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
        {{12,22,15},{0,0,0},{0,0,0},{8,19,10},{0,0,0},{12,25,15},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
        {{0,0,0},{0,0,0},{8,19,10},{0,0,0},{0,0,0},{0,0,0},{8,18,10},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
        {{0,0,0},{9,17,10},{0,0,0},{0,0,0},{0,0,0},{12,20,15},{0,0,0},{0,0,0},{0,0,0},{13,30,17},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
        {{0,0,0},{9,16,12},{12,25,15},{0,0,0},{12,20,15},{0,0,0},{11,23,14},{0,0,0},{0,0,0},{0,0,0},{13,21,17},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
        {{0,0,0},{0,0,0},{0,0,0},{8,18,10},{0,0,0},{11,23,14},{0,0,0},{0,0,0},{10,19,12},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
        {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{9,15,10},{0,0,0},{10,20,10},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
        {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{10,19,12},{9,15,10},{0,0,0},{0,0,0},{0,0,0},{13,22,17},{0,0,0},{0,0,0},{0,0,0}},
        {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{13,30,17},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{14,25,18},{0,0,0},{12,23,15},{0,0,0},{0,0,0}},
        {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{13,21,17},{0,0,0},{10,20,10},{0,0,0},{14,25,18},{0,0,0},{9,20,10},{0,0,0},{15,32,20},{0,0,0}},
        {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{13,22,17},{0,0,0},{9,20,10},{0,0,0},{0,0,0},{0,0,0},{26,40,15}},
        {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{12,23,15},{0,0,0},{0,0,0},{0,0,0},{22,40,25},{0,0,0}},
        {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{15,32,20},{0,0,0},{22,40,25},{0,0,0},{30,45,55}},
        {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{12,42,15},{0,0,0},{30,45,55},{0,0,0}}
    };

    while(1){
        displayMap();
        displayMenu();

        int menuOption = getValidInputOption(NO_OF_MENUITEMS);

        switch(menuOption){
            case 1:
                findShortestPath(graph);
                waitForKeypress();
                clearScreen();
                break;
            case 2:
                findMinTimeOrCostPath(graph, 1); // Passing 1 to fetch the time values from the graph matrix.
                waitForKeypress();
                clearScreen();
                break;
            case 3:
                findMinTimeOrCostPath(graph, 2); // Passing 2 to fetch the cost values from the graph matrix.
                waitForKeypress();
                clearScreen();
                break;
            case 4:
                return 0;
        }
    }
    return 0;
}