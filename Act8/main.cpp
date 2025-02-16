/*
Program to solve multiple graph-based tasks:
1. Minimum Spanning Tree using Kruskal's algorithm.
2. Traveling Salesman Problem (TSP) solution using Dynamic Programming (DP).
3. Maximum Information Flow using the Ford-Fulkerson algorithm.
4. Voronoi Diagram placeholder output for each point.

Author: Diego Iván Morales Gallardo
Date: November 2, 2024
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <stdexcept>
#include <climits>

using namespace std;

const int MAX_N = 16; // Maximum number of nodes

int N; // Number of neighborhoods or nodes
int distanceMatrix[MAX_N][MAX_N]; // Matrix storing distances between neighborhoods
int capacityMatrix[MAX_N][MAX_N]; // Matrix storing capacity values for flow calculations
int coords[MAX_N][2]; // Coordinates for each neighborhood (x, y)

// Variables for Kruskal's Algorithm
int parent[MAX_N]; // Union-Find parent array
int rankArr[MAX_N]; // Union-Find rank array

// Variables for TSP
int VISITED_ALL; // Mask representing all cities visited
int DP[1 << MAX_N][MAX_N]; // DP table for memoizing TSP subproblems

// Variables for Max Flow
int residual[MAX_N][MAX_N]; // Residual graph for Ford-Fulkerson
int parentFlow[MAX_N]; // Parent array to store paths in BFS for Ford-Fulkerson

// Edge struct for Kruskal's Algorithm
struct Edge {
    int u, v, weight; // Edge with start node u, end node v, and weight
};

/**
 * Finds the representative (root) of the set containing `u` using path compression.
 * @param u: Node for which the set representative is sought.
 * @return: Representative (root) of the set containing `u`.
 */
int findSet(int u);

/**
 * Merges the sets containing nodes `u` and `v` by rank.
 * @param u: One node of the set.
 * @param v: The other node of the set.
 */
void unionSets(int u, int v);

/**
 * Solves the Traveling Salesman Problem (TSP) using dynamic programming.
 * @param mask: Bitmask representing visited cities.
 * @param pos: Current city position in TSP path.
 * @return: Minimum cost to visit all cities starting from `pos` and following `mask`.
 */
int tsp(int mask, int pos);

/**
 * Performs a BFS to find an augmenting path in the residual graph.
 * @param s: Source node in the flow network.
 * @param t: Sink node in the flow network.
 * @return: True if there is a path from `s` to `t`, otherwise false.
 */
bool bfs(int s, int t);

int main() {
    try {
        ifstream fin("input.txt");
        if (!fin) {
            throw runtime_error("Error opening input file.");
        }

        fin >> N;
        if (fin.fail()) {
            throw runtime_error("Failed to read the number of neighborhoods (N).");
        }

        if (N < 1 || N > MAX_N) {
            throw runtime_error("Invalid value of N. It must be between 1 and " + to_string(MAX_N) + ".");
        }

        int i;
        int j;

        // Load the distance matrix from the input file
        for (i = 0; i < N; ++i) {
            for (j = 0; j < N; ++j) {
                fin >> distanceMatrix[i][j];
                if (fin.fail()) {
                    throw runtime_error("Failed to read distance matrix at position (" + to_string(i) + "," + to_string(j) + ").");
                }
                if (distanceMatrix[i][j] < 0) {
                    throw runtime_error("Negative distance found at position (" + to_string(i) + "," + to_string(j) + ").");
                }
            }
        }

        // Load the capacity matrix from the input file
        for (i = 0; i < N; ++i) {
            for (j = 0; j < N; ++j) {
                fin >> capacityMatrix[i][j];
                if (fin.fail()) {
                    throw runtime_error("Failed to read capacity matrix at position (" + to_string(i) + "," + to_string(j) + ").");
                }
                if (capacityMatrix[i][j] < 0) {
                    throw runtime_error("Negative capacity found at position (" + to_string(i) + "," + to_string(j) + ").");
                }
            }
        }

        // Load the coordinates for each neighborhood
        char ch;
        for (i = 0; i < N; ++i) {
            fin >> ch;
            if (ch != '(') {
                throw runtime_error("Expected '(' at the beginning of coordinates for point " + to_string(i + 1) + ".");
            }
            fin >> coords[i][0];
            if (fin.fail()) {
                throw runtime_error("Failed to read x-coordinate for point " + to_string(i + 1) + ".");
            }
            fin >> ch;
            if (ch != ',') {
                throw runtime_error("Expected ',' after x-coordinate for point " + to_string(i + 1) + ".");
            }
            fin >> coords[i][1];
            if (fin.fail()) {
                throw runtime_error("Failed to read y-coordinate for point " + to_string(i + 1) + ".");
            }
            fin >> ch;
            if (ch != ')') {
                throw runtime_error("Expected ')' at the end of coordinates for point " + to_string(i + 1) + ".");
            }
        }

        fin.close();

        // Task 1: Minimum Spanning Tree (MST) using Kruskal's Algorithm
        // Complexity: O(E log V) for sorting edges and finding MST
        for (i = 0; i < N; ++i) {
            parent[i] = i;
            rankArr[i] = 0;
        }

        Edge edges[MAX_N * MAX_N];
        int edgeCount = 0;

        for (i = 0; i < N; ++i) {
            for (j = i + 1; j < N; ++j) {
                if (distanceMatrix[i][j] != 0) {
                    edges[edgeCount].u = i;
                    edges[edgeCount].v = j;
                    edges[edgeCount].weight = distanceMatrix[i][j];
                    edgeCount++;
                }
            }
        }

        if (edgeCount == 0) {
            throw runtime_error("No edges found in the distance matrix. The graph is disconnected.");
        }

        for (i = 0; i < edgeCount - 1; ++i) {
            int minIdx = i;
            for (j = i + 1; j < edgeCount; ++j) {
                if (edges[j].weight < edges[minIdx].weight) {
                    minIdx = j;
                }
            }
            if (minIdx != i) {
                Edge temp = edges[i];
                edges[i] = edges[minIdx];
                edges[minIdx] = temp;
            }
        }

        Edge result[MAX_N];
        int e = 0;

        for (i = 0; i < edgeCount && e < N - 1; ++i) {
            int u = edges[i].u;
            int v = edges[i].v;

            int setU = findSet(u);
            int setV = findSet(v);

            if (setU != setV) {
                result[e++] = edges[i];
                unionSets(setU, setV);
            }
        }

        if (e != N - 1) {
            throw runtime_error("The graph is disconnected; cannot form a spanning tree.");
        }

        cout << "Way of wiring the neighborhoods with fiber (list of arcs):\n";
        for (i = 0; i < e; ++i) {
            char nodeU = 'A' + result[i].u;
            char nodeV = 'A' + result[i].v;
            cout << "(" << nodeU << "," << nodeV << ")\n";
        }

        // Task 2: Traveling Salesman Problem (TSP) using DP
        // Complexity: O(2^N * N) due to bitmask-based DP solution for TSP
        for (i = 0; i < (1 << N); ++i) {
            for (j = 0; j < N; ++j) {
                DP[i][j] = -1;
            }
        }

        VISITED_ALL = (1 << N) - 1;
        int minCost = tsp(1, 0);

        int mask = 1;
        int pos = 0;
        int path[MAX_N + 1];
        int pathIdx = 0;
        path[pathIdx++] = 0;

        while (mask != VISITED_ALL) {
            int bestCity = -1;
            int bestCost = INT_MAX;

            for (int city = 0; city < N; ++city) {
                if ((mask & (1 << city)) == 0) {
                    int newMask = mask | (1 << city);
                    int currentCost = distanceMatrix[pos][city] + DP[newMask][city];
                    if (currentCost < bestCost) {
                        bestCost = currentCost;
                        bestCity = city;
                    }
                }
            }

            if (bestCity == -1) {
                throw runtime_error("Failed to find the next city in TSP route.");
            }

            pos = bestCity;
            mask |= (1 << bestCity);
            path[pathIdx++] = bestCity;
        }

        path[pathIdx++] = 0;

        cout << "\nRoute to be followed by the mail delivery personnel:\n";
        for (i = 0; i < pathIdx; ++i) {
            char node = 'A' + path[i];
            cout << node;
            if (i != pathIdx - 1) {
                cout << " -> ";
            }
        }
        cout << "\n";

        // Task 3: Maximum Information Flow using Ford-Fulkerson Algorithm
        // Complexity: O(max_flow * E), where max_flow is the maximum flow found
        for (i = 0; i < N; ++i) {
            for (j = 0; j < N; ++j) {
                residual[i][j] = capacityMatrix[i][j];
            }
        }

        int maxFlow = 0;
        int pathFlow;

        while (bfs(0, N - 1)) {
            pathFlow = INT_MAX;

            for (int v = N - 1; v != 0; v = parentFlow[v]) {
                int u = parentFlow[v];
                pathFlow = min(pathFlow, residual[u][v]);
            }

            for (int v = N - 1; v != 0; v = parentFlow[v]) {
                int u = parentFlow[v];
                residual[u][v] -= pathFlow;
                residual[v][u] += pathFlow;
            }

            maxFlow += pathFlow;
        }

        cout << "\nMaximum information flow value from node A to node ";
        char nodeT = 'A' + N - 1;
        cout << nodeT << ": " << maxFlow << "\n";

        // Task 4: Voronoi Diagram placeholder output
        // Complexity: O(N), simply iterating through each point to print coordinates
        cout << "\nList of polygons (each element is a list of points (x,y)):\n";
        for (i = 0; i < N; ++i) {
            cout << "Polygon for exchange " << i + 1 << ":\n";
            cout << "(" << coords[i][0] << "," << coords[i][1] << ")\n";
        }

    } catch (const exception& ex) {
        cerr << "Error: " << ex.what() << "\n";
        return 1;
    }

    return 0;
}

int findSet(int u) {
    if (parent[u] != u) {
        parent[u] = findSet(parent[u]);
    }
    return parent[u];
}

void unionSets(int u, int v) {
    if (rankArr[u] < rankArr[v]) {
        parent[u] = v;
    } else if (rankArr[u] > rankArr[v]) {
        parent[v] = u;
    } else {
        parent[v] = u;
        rankArr[u]++;
    }
}

int tsp(int mask, int pos) {
    if (mask == VISITED_ALL) {
        return distanceMatrix[pos][0];
    }
    if (DP[mask][pos] != -1) {
        return DP[mask][pos];
    }

    int ans = INT_MAX;
    bool found = false;

    for (int city = 0; city < N; ++city) {
        if ((mask & (1 << city)) == 0) {
            int newAns = distanceMatrix[pos][city] + tsp(mask | (1 << city), city);
            if (newAns < ans) {
                ans = newAns;
                found = true;
            }
        }
    }

    if (!found) {
        throw runtime_error("No valid path found in TSP.");
    }

    DP[mask][pos] = ans;
    return ans;
}

bool bfs(int s, int t) {
    bool visited[MAX_N];
    int queue[MAX_N];
    int front = 0;
    int back = 0;

    for (int i = 0; i < N; ++i) {
        visited[i] = false;
    }

    queue[back++] = s;
    visited[s] = true;
    parentFlow[s] = -1;

    while (front < back) {
        int u = queue[front++];

        for (int v = 0; v < N; ++v) {
            if (!visited[v] && residual[u][v] > 0) {
                queue[back++] = v;
                parentFlow[v] = u;
                visited[v] = true;

                if (v == t) {
                    return true;
                }
            }
        }
    }

    return false;
}
