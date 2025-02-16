/*
    Program that implements the Dijkstra and Floyd-Warshall algorithms to find the shortest distances
    between nodes in a graph represented by an adjacency matrix.
    Author: Diego Iván Morales Gallardo
    Creation date: September 26, 2024
    Overall complexity: The program implements two algorithms to find the shortest distances in a graph. 
    The Dijkstra algorithm is executed from each node, resulting in a complexity of O(n^3). 
    The Floyd-Warshall algorithm also has a complexity of O(n^3). 
    Therefore, the total complexity of the program is O(n^3), where n is the number of nodes in the graph.
*/

#include <iostream>
#include <fstream>

#define INF 1000000000  // Represents an infinite distance
#define MAX_NODES 1000  // Maximum number of nodes allowed in the graph

using namespace std;

int nodeCount;
int adjMatrix[MAX_NODES][MAX_NODES];  // Adjacency matrix that stores the distances between nodes
int distancesArray[MAX_NODES];        // Stores the minimum distances from a starting node in Dijkstra
bool visitedNodes[MAX_NODES];         // Tracks visited nodes in Dijkstra
int floydDistancesMatrix[MAX_NODES][MAX_NODES];  // Matrix that stores the shortest distances in Floyd-Warshall

/*
    Main function that reads input data and executes the Dijkstra and Floyd-Warshall algorithms.
    Input: Reads an adjacency matrix representing the distances between nodes in a graph.
    Output: Prints the shortest distances calculated by Dijkstra from each node to others. Prints the distance matrix calculated by Floyd-Warshall.
    Complexity of the main: The main function reads the adjacency matrix and then runs both the Dijkstra and Floyd-Warshall algorithms.
    Reading the matrix has a complexity of O(n^2). The Dijkstra algorithm, executed from each node, has a complexity of O(n^3).
    After that, the Floyd-Warshall algorithm also has a complexity of O(n^3).
    In total, the complexity of the main function is O(n^3).
*/
int main() {
    // Read data from standard input using a file buffer
    ifstream inputFile;
    inputFile.std::basic_ios<char>::rdbuf(std::cin.rdbuf());

    // Read the number of nodes in the graph
    inputFile >> nodeCount;

    // Read the adjacency matrix representing the distances between nodes
    for (int i = 0; i < nodeCount; ++i) {
        for (int j = 0; j < nodeCount; ++j) {
            int weight;
            inputFile >> weight;
            adjMatrix[i][j] = weight;
        }
    }

    // Dijkstra algorithm to calculate the shortest distances from each node
    cout << "Dijkstra :" << endl;
    for (int startNode = 0; startNode < nodeCount; ++startNode) {
        // Initialize distances to infinity and mark all nodes as unvisited
        for (int i = 0; i < nodeCount; ++i) {
            distancesArray[i] = INF;
            visitedNodes[i] = false;
        }
        distancesArray[startNode] = 0;

        int count = 0;
        // Iterate while there are unprocessed nodes
        while (count < nodeCount) {
            // Find the unvisited node with the minimum distance
            int currentNode = -1;
            int minDistance = INF;
            for (int i = 0; i < nodeCount; ++i) {
                if (!visitedNodes[i] && distancesArray[i] < minDistance) {
                    minDistance = distancesArray[i];
                    currentNode = i;
                }
            }

            if (currentNode == -1) {
                // If there are no more reachable nodes, end the loop
                count = nodeCount;
            } else {
                visitedNodes[currentNode] = true;

                // Update distances for adjacent nodes
                for (int nextNode = 0; nextNode < nodeCount; ++nextNode) {
                    if (adjMatrix[currentNode][nextNode] != -1) {
                        if (distancesArray[nextNode] > distancesArray[currentNode] + adjMatrix[currentNode][nextNode]) {
                            distancesArray[nextNode] = distancesArray[currentNode] + adjMatrix[currentNode][nextNode];
                        }
                    }
                }
                count++;
            }
        }

        // Print the minimum distances from the current node to others
        for (int destinationNode = 0; destinationNode < nodeCount; ++destinationNode) {
            if (destinationNode != startNode) {
                if (distancesArray[destinationNode] != INF) {
                    cout << "node " << startNode + 1 << " to node " << destinationNode + 1 << " : " << distancesArray[destinationNode] << endl;
                }
            }
        }
    }

    // Initialize the distance matrix for Floyd-Warshall
    for (int i = 0; i < nodeCount; ++i) {
        for (int j = 0; j < nodeCount; ++j) {
            if (adjMatrix[i][j] != -1) {
                floydDistancesMatrix[i][j] = adjMatrix[i][j];
            } else {
                floydDistancesMatrix[i][j] = INF;
            }
        }
        floydDistancesMatrix[i][i] = 0;
    }

    // Apply the Floyd-Warshall algorithm
    for (int k = 0; k < nodeCount; ++k) {
        for (int i = 0; i < nodeCount; ++i) {
            if (floydDistancesMatrix[i][k] != INF) {
                for (int j = 0; j < nodeCount; ++j) {
                    if (floydDistancesMatrix[k][j] != INF) {
                        if (floydDistancesMatrix[i][j] > floydDistancesMatrix[i][k] + floydDistancesMatrix[k][j]) {
                            floydDistancesMatrix[i][j] = floydDistancesMatrix[i][k] + floydDistancesMatrix[k][j];
                        }
                    }
                }
            }
        }
    }

    // Print the shortest distance matrix calculated by Floyd-Warshall
    cout << "Floyd :" << endl;
    for (int i = 0; i < nodeCount; ++i) {
        for (int j = 0; j < nodeCount; ++j) {
            if (floydDistancesMatrix[i][j] >= INF / 2) {
                cout << "-1";
            } else {
                cout << floydDistancesMatrix[i][j];
            }
            if (j != nodeCount - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }

    return 0;
}
