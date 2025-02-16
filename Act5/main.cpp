/*
    Program that implements Dijkstra’s Algorithm using an adjacency list and a min-heap.
    It reads a graph from an input file, processes it, and determines the shortest path
    from a specified starting node to all other nodes.  
    Author: Diego Ivan Morales Gallardo A01643382
    Creation date: September 26, 2024
    Overall complexity: The program implements Dijkstra's Algorithm using an adjacency list and a min-heap.
    The algorithm has a time complexity of O((n + m) log n), where n is the number of nodes and m is the number of edges.
    The heap operations (insertion, extraction, and updates) take O(log n) time, and the relaxation of edges is performed
    for each edge in the graph, resulting in an efficient handling of sparse graphs.
*/

#include <iostream>
#include <fstream>

#define NODES_MAX 321271  // Maximum number of nodes (indexed from 1)
#define INF 1000000000    // A large value representing infinity

// Structure representing an edge in the adjacency list
struct Edge {
    int to;        // Destination node of the edge
    int weight;    // Weight of the edge
    Edge* next;    // Pointer to the next edge in the adjacency list
};

// Global variables for graph representation and Dijkstra's algorithm
Edge* adj[NODES_MAX];       // Adjacency list for graph representation
int dist[NODES_MAX];        // Distance array for shortest paths
bool visited[NODES_MAX];    // Array to mark visited nodes
int heap[NODES_MAX];        // Min-heap for priority queue implementation
int heapPos[NODES_MAX];     // Position of each node in the heap
int heapSize = 0;           // Size of the min-heap

/*
    Function: parseInt
    Converts a substring of a character buffer into an integer.
    Skips spaces and extracts digits to form the integer value.
    Parameters:
        str: The character buffer containing the input string.
        index: The current position in the buffer, updated during parsing.
    Returns:
        The parsed integer value.
    parseInt complexity: O(k), where k is the number of characters in the string to parse the integer.
*/
int parseInt(char* str, int& index) {
    while (str[index] == ' ' || str[index] == '\t') {
        index++;
    }
    
    int val = 0;
    while (str[index] >= '0' && str[index] <= '9') {
        val = val * 10 + (str[index] - '0');
        index++;
    }
    return val;
}

/*
    Function: swap
    Swaps two elements in the heap and updates their positions.
    Parameters:
        i: Index of the first element in the heap.
        j: Index of the second element in the heap.
    swap complexity: O(1), constant time to swap two elements in the heap and update their positions.
*/
void swap(int i, int j) {
    int temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
    heapPos[heap[i]] = i;
    heapPos[heap[j]] = j;
}

/*
    Function: siftUp
    Reorganizes the heap by moving a node upward to maintain heap order.
    Parameters:
        idx: The index of the node to be sifted up in the heap.
    siftUp complexity: O(log n), where n is the number of nodes in the heap. The function maintains the heap order
    by moving a node upwards, and in the worst case, it travels up the height of the heap, which is log n.
*/
void siftUp(int idx) {
    while (idx > 1 && dist[heap[idx]] < dist[heap[idx / 2]]) {
        swap(idx, idx / 2);
        idx = idx / 2;
    }
}

/*
    Function: siftDown
    Reorganizes the heap by moving a node downward to maintain heap order.
    Parameters:
        idx: The index of the node to be sifted down in the heap.
    siftDown complexity: O(log n), where n is the number of nodes in the heap. This function ensures that the heap
    order is maintained by moving a node downwards, with a worst-case time of log n, proportional to the height of the heap.
*/
void siftDown(int idx) {
    while (2 * idx <= heapSize) {
        int child = 2 * idx;
        if (child + 1 <= heapSize && dist[heap[child + 1]] < dist[heap[child]]) {
            child++;
        }
        if (dist[heap[idx]] <= dist[heap[child]]) {
            idx = heapSize + 1;  // Exit the loop
        } else {
            swap(idx, child);
            idx = child;
        }
    }
}

/*
    Function: insert
    Inserts a new node into the min-heap and maintains the heap order.
    Parameters:
        node: The node to be inserted into the heap.
    insert complexity: O(log n), where n is the number of nodes in the heap. Inserting a new node into the heap
    requires placing the node at the end and then sifting it up to maintain heap order.
*/
void insert(int node) {
    heapSize++;
    heap[heapSize] = node;
    heapPos[node] = heapSize;
    siftUp(heapSize);
}

/*
    Function: extractMin
    Extracts the node with the minimum distance from the heap.
    Returns:
        The node with the minimum distance from the heap.
    extractMin complexity: O(log n), where n is the number of nodes in the heap. Extracting the minimum node from
    the heap requires removing the root and sifting down the new root to restore the heap property.
*/
int extractMin() {
    int minNode = heap[1];
    heap[1] = heap[heapSize];
    heapPos[heap[1]] = 1;
    heapSize--;
    siftDown(1);
    return minNode;
}

/*
    Complexity of main: O((n + m) log n), where n is the number of nodes and m is the number of edges.
    The adjacency list initialization takes O(n). For Dijkstra's algorithm, the min-heap operations (insertion,
    extraction) and edge relaxation are performed for each edge, leading to a complexity of O((n + m) log n).
    This ensures an efficient computation of the shortest paths in sparse graphs.
*/
int main() {
    std::ifstream inFile("/dev/stdin");  // Input file containing the graph data
    std::ofstream outFile("output.txt"); // Output file for results

    // Initialize the adjacency list (graph) with null pointers
    for (int i = 0; i < NODES_MAX; i++) {
        adj[i] = NULL;
    }

    // Read the input graph data from the file
    char buffer[256];
    while (inFile.getline(buffer, 256)) {
        bool processLine = true;
        
        if (buffer[0] == 'c') {
            // Skip comment lines
            processLine = false;
        } else if (buffer[0] == 'p') {
            // Skip problem description lines (not needed for this implementation)
            processLine = false;
        }

        if (processLine && buffer[0] == 'a') {
            // Process arc lines that define edges in the graph
            int idx = 1;
            int fromNode = parseInt(buffer, idx);  // Source node
            int toNode = parseInt(buffer, idx);    // Destination node
            int edgeWeight = parseInt(buffer, idx); // Weight of the edge

            // Add edge from fromNode to toNode in the adjacency list
            Edge* edge = new Edge;
            edge->to = toNode;
            edge->weight = edgeWeight;
            edge->next = adj[fromNode];
            adj[fromNode] = edge;
        }
    }

    // Initialize the distance and visited arrays
    for (int i = 0; i < NODES_MAX; i++) {
        dist[i] = INF;
        visited[i] = false;
        heapPos[i] = -1;
    }

    int startNode = 7;  // Starting node for Dijkstra's algorithm
    dist[startNode] = 0;
    heapSize = 0;
    insert(startNode);

    // Dijkstra's algorithm: process nodes to find shortest paths
    while (heapSize > 0) {
        int u = extractMin();  // Get the node with the minimum distance
        if (!visited[u]) {
            visited[u] = true;

            // Relaxation step: update distances to adjacent nodes
            Edge* edge = adj[u];
            while (edge != NULL) {
                int v = edge->to;
                int weight = edge->weight;
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    if (heapPos[v] == -1) {
                        insert(v);
                    } else {
                        siftUp(heapPos[v]);
                    }
                }
                edge = edge->next;
            }
        }
    }

    // Output the shortest distances from the start node to all other nodes
    for (int i = 1; i < NODES_MAX; i++) {
        if (dist[i] < INF) {
            std::cout << "Node " << startNode << " to Node " << i << " : " << dist[i] << std::endl;
            outFile << "Node " << startNode << " to Node " << i << " : " << dist[i] << std::endl;
        } else {
            std::cout << "Node " << startNode << " to Node " << i << " : Unreachable" << std::endl;
            outFile << "Node " << startNode << " to Node " << i << " : Unreachable" << std::endl;
        }
    }

    // Free dynamically allocated memory for the adjacency list
    for (int i = 0; i < NODES_MAX; i++) {
        Edge* edge = adj[i];
        while (edge != NULL) {
            Edge* temp = edge;
            edge = edge->next;
            delete temp;
        }
    }

    // Close the output file
    outFile.close();

    return 0;
}
