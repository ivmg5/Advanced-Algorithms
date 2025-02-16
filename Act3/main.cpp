// Program to check if all non-empty input strings are distinct
// Author: Diego Ivan Morales Gallardo
// Date: September 17, 2024

// This program uses a hash table with a polynomial rolling hash function to store and check for duplicate strings.
// The hashing strategy chosen is a simple polynomial rolling hash, which is efficient and has good distribution properties for strings.
// Collision resolution is handled using linear probing.
// The overall time complexity of the program is O(N * L), where N is the number of input strings and L is the average length of the strings.
// The space complexity is O(M), where M is the size of the hash table.

#include <iostream>
#include <fstream>

using namespace std;

const int PRIME_BASE = 31;
const long long MODULO = 1e9 + 9;
const int HASH_TABLE_SIZE = 200003; // A prime number close to 200,000 to reduce collisions
const string EMPTY_SLOT = "#";

string hashTable[HASH_TABLE_SIZE];

// Initializes the hash table by setting all slots to EMPTY_SLOT.
// Complexity: O(HASH_TABLE_SIZE).
void initializeHashTable() {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        hashTable[i] = EMPTY_SLOT;
    }
}

// Computes the hash value of a given string using a polynomial rolling hash function.
// @param str The input string to compute the hash for.
// @return The computed hash value as a long long integer.
// Complexity: O(L), where L is the length of the string.
long long computeHashValue(const string& str) {
    long long hashValue = 0;
    for (unsigned char character : str) {
        hashValue = (hashValue * PRIME_BASE + character) % MODULO;
    }
    return hashValue;
}

// Finds the index of a string in the hash table or the next available empty slot using linear probing.
// @param str The string to search for in the hash table.
// @param found Reference to a bool that will be set to true if the string is found.
// @return The index in the hash table where the string is found or should be inserted.
// Complexity: O(1) on average, O(N) in the worst case due to collisions
int findStringInHashTable(const string& str, bool& found) {
    long long hashValue = computeHashValue(str);
    int hashIndex = hashValue % HASH_TABLE_SIZE;

    // Linear probing to handle collisions
    while (hashTable[hashIndex] != EMPTY_SLOT && hashTable[hashIndex] != str) {
        hashIndex = (hashIndex + 1) % HASH_TABLE_SIZE;
    }

    found = (hashTable[hashIndex] == str);
    return hashIndex;
}

int main() {
    initializeHashTable();

    string inputString = "";
    bool areAllStringsDistinct = true;

    // Read each line from the input and process non-empty lines
    while (getline(cin, inputString)) {
        if (!inputString.empty()) {
            bool found = false;
            int hashIndex = findStringInHashTable(inputString, found);

            if (found) {
                areAllStringsDistinct = false;
            } else {
                hashTable[hashIndex] = inputString;
            }
        }
    }

    if (areAllStringsDistinct) {
        cout << "All strings are distinct" << endl;
    } else {
        cout << "Strings are not all distinct" << endl;
    }

    return 0;
}