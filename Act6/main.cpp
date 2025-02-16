/*
    Simulated Annealing for Solving the Traveling Salesman Problem (TSP)
    This program implements a simulated annealing algorithm to find an approximate solution 
    to the TSP by minimizing the total tour distance.

    Author: Diego Iván Morales Gallardo 
    Creation/Modification Date: November 22, 2024
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <random>

/**
 * Structure to represent a city with a unique identifier and its coordinates.
 */
struct City {
    int id;
    double x;
    double y;
};

/**
 * Calculates the Euclidean distance between two cities.
 * 
 * @param cityA The first city.
 * @param cityB The second city.
 * @return The Euclidean distance between cityA and cityB.
 * 
 * Complexity: O(1), as it performs a fixed number of arithmetic operations.
 */
double calculateDistance(const City& cityA, const City& cityB) {
    double deltaX = cityA.x - cityB.x;
    double deltaY = cityA.y - cityB.y;

    return sqrt(deltaX * deltaX + deltaY * deltaY);
}

/**
 * Calculates the total distance of a tour based on the provided city sequence.
 * 
 * @param cities A vector containing all the cities.
 * @param tour A vector of city indices representing the tour sequence.
 * @return The total distance of the tour.
 * 
 * Complexity: O(n), where n is the number of cities in the tour. Each city pair is compared once.
 */
double calculateTotalDistance(const std::vector<City>& cities, const std::vector<int>& tour) {
    double totalDistance = 0.0;
    int tourSize = tour.size();

    for (int i = 0; i < tourSize; ++i) {
        const City& from = cities[tour[i]];
        const City& to = cities[tour[(i + 1) % tourSize]];
        totalDistance += calculateDistance(from, to);
    }

    return totalDistance;
}

/**
 * Modifies the given tour by reversing the sequence of cities between two indices.
 * 
 * @param tour A vector of city indices representing the current tour.
 * @param startIdx The start index of the segment to be reversed.
 * @param endIdx The end index of the segment to be reversed.
 * 
 * Complexity: O(k), where k is the length of the segment being reversed.
 */
void twoOptSwap(std::vector<int>& tour, int startIdx, int endIdx) {
    while (startIdx < endIdx) {
        std::swap(tour[startIdx % tour.size()], tour[endIdx % tour.size()]);
        ++startIdx;
        --endIdx;
    }
}

/**
 * Main function to execute the simulated annealing algorithm for solving the TSP.
 * 
 * Complexity: The overall complexity depends on:
 * - The number of iterations for temperature reduction: O(log(initialTemperature / minTemperature)).
 * - The number of iterations per temperature level: O(iterationsPerTemperature).
 * - The cost of evaluating each tour: O(n), where n is the number of cities.
 * 
 * Overall: O((log(T_initial / T_min)) * iterationsPerTemperature * n).
 */
int main() {
    int numCities;

    // Read the number of cities and their details.
    std::cin >> numCities;
    std::vector<City> cities(numCities);

    for (int i = 0; i < numCities; ++i) {
        int id;
        double xCoord, yCoord;

        std::cin >> id >> xCoord >> yCoord;
        cities[i] = {id - 1, xCoord, yCoord}; // Adjust indices to start from 0.
    }

    // Initialize random number generators for the simulated annealing process.
    std::mt19937 randomGenerator(std::random_device{}());
    std::uniform_real_distribution<> realDist(0.0, 1.0);
    std::uniform_int_distribution<> intDist(0, numCities - 1);

    // Create an initial random tour.
    std::vector<int> currentTour(numCities);
    for (int i = 0; i < numCities; ++i) {
        currentTour[i] = i;
    }
    std::shuffle(currentTour.begin(), currentTour.end(), randomGenerator);

    double currentTourDistance = calculateTotalDistance(cities, currentTour);

    // Simulated Annealing parameters
    const double INITIAL_TEMPERATURE = 10000.0; // Starting temperature
    const double MIN_TEMPERATURE = 1e-8;        // Stopping temperature
    const double COOLING_RATE = 0.995;          // Temperature decay rate
    const int ITERATIONS_PER_TEMP = 1000;       // Iterations per temperature level

    std::vector<int> bestTour = currentTour;
    double bestTourDistance = currentTourDistance;

    double temperature = INITIAL_TEMPERATURE;

    while (temperature > MIN_TEMPERATURE) {
        for (int iter = 0; iter < ITERATIONS_PER_TEMP; ++iter) {
            // Generate a random neighbor solution.
            int idx1 = intDist(randomGenerator);
            int idx2 = intDist(randomGenerator);

            while (idx2 == idx1) {
                idx2 = intDist(randomGenerator);
            }

            int startIdx = std::min(idx1, idx2);
            int endIdx = std::max(idx1, idx2);

            // Reverse a segment of the current tour to create a new tour.
            std::vector<int> newTour = currentTour;
            twoOptSwap(newTour, startIdx, endIdx);

            double newTourDistance = calculateTotalDistance(cities, newTour);
            double distanceDelta = newTourDistance - currentTourDistance;

            // Accept new solution based on simulated annealing probability.
            if (distanceDelta < 0 || exp(-distanceDelta / temperature) > realDist(randomGenerator)) {
                currentTour = newTour;
                currentTourDistance = newTourDistance;

                // Update the best solution found so far.
                if (currentTourDistance < bestTourDistance) {
                    bestTour = currentTour;
                    bestTourDistance = currentTourDistance;
                }
            }
        }

        // Reduce the temperature according to the cooling rate.
        temperature *= COOLING_RATE;
    }

    // Output the best tour and its total distance.
    std::cout << "Best tour length: " << bestTourDistance << std::endl;
    std::cout << "Best tour:" << std::endl;

    for (int i = 0; i < numCities; ++i) {
        std::cout << cities[bestTour[i]].id + 1 << " ";
    }

    std::cout << std::endl;

    return 0;
}
