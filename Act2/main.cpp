/*
    Program that implements dynamic programming and greedy algorithms to calculate the minimum number of coins needed for making change, 
    and sorts the results in descending order of denominations.
    Author: Diego Ivan Morales Gallardo
    Creation Date: August 20, 2024
    General Complexity: The overall complexity of the dynamic programming approach is O(n * m), where n is the number of denominations and m is the change amount. 
    The greedy approach has a complexity of O(n), where n is the number of denominations.
*/

#include <iostream>

using namespace std;

/*
    Function that sorts the denominations array in descending order while maintaining
    the corresponding count of coins in the coinCount array, and then prints the count of coins for each denomination.
    Parameters:
    - coinCount[]: Array holding the count of coins for each denomination.
    - denominations[]: Array holding the different coin denominations.
    - numDenominations: Number of different coin denominations.
    Complexity: The complexity of this sorting function is O(n^2), where n is the number of denominations.
*/
void sortAndPrintResults(int coinCount[], int denominations[], int numDenominations) {
    for (int i = 0; i < numDenominations - 1; ++i) {
        for (int j = 0; j < numDenominations - i - 1; ++j) {
            if (denominations[j] < denominations[j + 1]) {
                int tempDenomination = denominations[j];
                denominations[j] = denominations[j + 1];
                denominations[j + 1] = tempDenomination;
                int tempCoinCount = coinCount[j];
                coinCount[j] = coinCount[j + 1];
                coinCount[j + 1] = tempCoinCount;
            }
        }
    }

    for (int i = 0; i < numDenominations; ++i) {
        cout << coinCount[i] << endl;
    }
}

/*
    Function that calculates the minimum number of coins needed to make the change using dynamic programming
    and then sorts and prints the result in descending order of denominations.
    Parameters:
    - denominations[]: Array holding the different coin denominations.
    - numDenominations: Number of different coin denominations.
    - productPrice: Price of the product being purchased.
    - paymentAmount: Total amount paid by the customer.
    Complexity: The complexity of this dynamic programming approach is O(n * m), where n is the number of denominations and m is the amount of change to be made.
*/
void dynamicChangeMaking(int denominations[], int numDenominations, int productPrice, int paymentAmount) {
    int changeAmount = paymentAmount - productPrice;
    int minCoinsRequired[changeAmount + 1];
    int coinCount[numDenominations];

    minCoinsRequired[0] = 0;
    for (int i = 1; i <= changeAmount; ++i) {
        minCoinsRequired[i] = changeAmount + 1;
    }

    for (int currentAmount = 1; currentAmount <= changeAmount; ++currentAmount) {
        for (int j = 0; j < numDenominations; ++j) {
            if (currentAmount >= denominations[j]) {
                minCoinsRequired[currentAmount] = min(minCoinsRequired[currentAmount], minCoinsRequired[currentAmount - denominations[j]] + 1);
            }
        }
    }

    int remainingChange = changeAmount;
    for (int i = 0; i < numDenominations; ++i) {
        coinCount[i] = 0;
    }

    for (int i = 0; i < numDenominations; ++i) {
        while (remainingChange >= denominations[i] && minCoinsRequired[remainingChange] == minCoinsRequired[remainingChange - denominations[i]] + 1) {
            coinCount[i]++;
            remainingChange -= denominations[i];
        }
    }

    sortAndPrintResults(coinCount, denominations, numDenominations);
}

/*
    Function that calculates the change using a greedy algorithm, which selects the largest possible denominations first,
    and then sorts and prints the result in descending order of denominations.
    Parameters:
    - denominations[]: Array holding the different coin denominations, assumed to be sorted in descending order.
    - numDenominations: Number of different coin denominations.
    - productPrice: Price of the product being purchased.
    - paymentAmount: Total amount paid by the customer.
    Complexity: The complexity of this greedy approach is O(n), where n is the number of denominations.
*/
void greedyChangeMaking(int denominations[], int numDenominations, int productPrice, int paymentAmount) {
    int changeAmount = paymentAmount - productPrice;
    int coinCount[numDenominations];

    for (int i = 0; i < numDenominations; ++i) {
        coinCount[i] = 0;
    }

    for (int i = 0; i < numDenominations; ++i) {
        while (changeAmount >= denominations[i]) {
            coinCount[i]++;
            changeAmount -= denominations[i];
        }
    }

    sortAndPrintResults(coinCount, denominations, numDenominations);
}

int main() {
    int numDenominations;
    cin >> numDenominations;

    int denominations[numDenominations];
    for (int i = 0; i < numDenominations; ++i) {
        cin >> denominations[i];
    }

    int productPrice, paymentAmount;
    cin >> productPrice >> paymentAmount;

    dynamicChangeMaking(denominations, numDenominations, productPrice, paymentAmount);
    greedyChangeMaking(denominations, numDenominations, productPrice, paymentAmount);

    return 0;
}