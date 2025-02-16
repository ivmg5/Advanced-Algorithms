# **Algorithmic Applications for Computational Problems**
> *A portfolio of projects implementing various algorithms and data structures to solve computational problems.*

## **Introduction**
This repository contains a collection of algorithmic implementations designed to solve a variety of computational challenges. Each project explores fundamental concepts in sorting, dynamic programming, graph algorithms, and string processing, applying them to real-world scenarios.

## **Project Description**
- **Main functionality:** The portfolio includes implementations of well-known algorithms such as Merge Sort, Dynamic Programming for coin change, Hash Tables for duplicate detection, Dijkstra's algorithm, Simulated Annealing for TSP, and graph-based problems including MST, Max Flow, and Voronoi diagrams.
- **Technologies used:** C++ for core algorithmic implementations, utilizing standard input and output handling, file operations, and optimized data structures.
- **Challenges faced:** Managing computational complexity, optimizing memory usage, and implementing advanced algorithmic paradigms such as simulated annealing.

## **Activities Overview**

### **Activity 1: Merge Sort for Sorting Decimal Numbers**
This program implements the **Merge Sort** algorithm to sort an array of decimal numbers in **descending order**.

- **Key functions:** `mergeSort` recursively sorts subarrays, `merge` combines sorted halves efficiently.
- **Objective:** Demonstrate the power of divide-and-conquer sorting with an optimal complexity of **O(n log n)**.

### **Activity 2: Minimum Coin Change using Dynamic Programming and Greedy Algorithms**
This program determines the **minimum number of coins needed** to provide change using two approaches:
1. **Dynamic Programming (O(n * m))** for an optimal solution.
2. **Greedy Algorithm (O(n))** for an efficient but not always optimal approach.

- **Key functions:** `dynamicChangeMaking` computes optimal change, `greedyChangeMaking` follows a heuristic approach.
- **Objective:** Explore algorithmic trade-offs between exact optimization and heuristic approximations.

### **Activity 3: Detecting Duplicate Strings using Hash Tables**
Implements a **hash table with polynomial rolling hashing** and **linear probing** for efficient duplicate string detection.

- **Key functions:** `computeHashValue` generates unique hash values, `findStringInHashTable` locates or inserts strings.
- **Objective:** Demonstrate **O(1)** average-time complexity lookup for duplicate detection.

### **Activity 4: Shortest Path in Graphs (Dijkstra & Floyd-Warshall)**
This program computes the **shortest paths** in a graph using:
1. **Dijkstra’s Algorithm (O(n²))** for single-source shortest path computation.
2. **Floyd-Warshall Algorithm (O(n³))** for all-pairs shortest paths.

- **Key functions:** `Dijkstra` iteratively updates shortest paths, `FloydWarshall` computes a complete distance matrix.
- **Objective:** Compare different shortest path algorithms and analyze their trade-offs.

### **Activity 5: Optimized Dijkstra with Min-Heap for Large Graphs**
Enhances **Dijkstra’s algorithm** using an **adjacency list** and a **min-heap** (priority queue) to improve efficiency.

- **Key functions:** `siftUp` and `siftDown` maintain the heap, `extractMin` efficiently retrieves the closest node.
- **Objective:** Optimize shortest path calculations for **sparse graphs** with **O((n + m) log n)** complexity.

### **Activity 6: Solving the Traveling Salesman Problem (TSP) with Simulated Annealing**
Implements **Simulated Annealing** to approximate the optimal tour for the **Traveling Salesman Problem (TSP)**.

- **Key functions:** `calculateDistance` computes pairwise distances, `twoOptSwap` perturbs the tour to escape local optima.
- **Objective:** Use probabilistic optimization to solve NP-hard problems efficiently.

### **Activity 7: String Analysis for Malicious Code Detection**
Applies advanced string-processing algorithms to analyze transmissions and detect malicious patterns.

- **Key functions:**
  - `KMPSearch` (Knuth-Morris-Pratt) for fast substring search.
  - `Manacher` for detecting the **longest palindrome** in a string.
  - `LongestCommonSubstring` (dynamic programming) to find shared segments between two sequences.
- **Objective:** Utilize multiple algorithms for efficient text analysis and cybersecurity applications.

### **Activity 8: Graph-Based Problems (MST, Max Flow, Voronoi, TSP)**
A collection of graph algorithms solving different computational problems:
1. **Minimum Spanning Tree (MST)** using **Kruskal's algorithm (O(E log V))**.
2. **Traveling Salesman Problem (TSP)** with **Dynamic Programming (O(2^N * N))**.
3. **Maximum Information Flow** with **Ford-Fulkerson Algorithm (O(max_flow * E))**.
4. **Voronoi Diagram Approximation** for geometric partitioning.

- **Key functions:** `findSet` (Union-Find for MST), `tsp` (bitmask DP), `bfs` (augmenting path search in Max Flow).
- **Objective:** Showcase advanced graph algorithms for real-world network problems.

## **Table of Contents**
1. [Introduction](#introduction)
2. [Project Description](#project-description)
3. [Activities Overview](#activities-overview)
4. [Installation](#installation)
5. [Usage](#usage)
6. [License](#license)

## **Installation**
1. **Prerequisites:**
   - **C++ Compiler**
   - **Standard C++ Libraries**

2. **Clone the repository:**
   ```bash
   git clone https://github.com/yourusername/Advanced-Algorithms.git
   cd Act1
   ```

3. Compile and run each activity:
   ```bash
   g++ main.cpp -o main
   ./main
   ```

## **Usage**

Each activity follows a simple input-output model:
1. Run the program: Compile and execute the corresponding C++ file.
2. Provide input (if required): Some programs expect standard input (e.g., arrays, graphs).
3. Review output: The results will be displayed on the console or written to a file.

## **License**

This project is licensed under the MIT License.

## **Status Badges**
[![Build Status](https://img.shields.io/badge/status-active-brightgreen)](#) [![Code Coverage](https://img.shields.io/badge/coverage-80%25-yellowgreen)](#)
