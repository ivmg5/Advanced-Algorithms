/*
 * Program to analyze transmissions and detect malicious codes, palindromes, and longest common substrings.
 * Author: Diego Ivan Morales Gallardo
 * Date: September 6, 2024
 */

#include <iostream>
#include <fstream>
#include <cstring>

#define MAX_LEN 100000

using namespace std;

/* 
 * Function to compute the Longest Prefix Suffix (LPS) array used in KMP algorithm.
 * @param pattern: the pattern to be searched
 * @param M: length of the pattern
 * @param lps: array to store the longest prefix which is also a suffix
 */
void computeLPSArray(char* pattern, int M, int* lps) {
    int length = 0;
    lps[0] = 0;
    int i = 1;
    
    // Build the LPS array based on pattern characters
    while (i < M) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

/* 
 * KMP algorithm to search for the pattern in a given text.
 * @param text: the text in which the pattern is searched
 * @param pattern: the pattern to be searched
 * @param N: length of the text
 * @param M: length of the pattern
 * @param pos: reference to store the position of the pattern match
 * @return: true if the pattern is found, otherwise false
 */
bool KMPSearch(char* text, char* pattern, int N, int M, int& pos) {
    int lps[MAX_LEN];
    computeLPSArray(pattern, M, lps);
    
    int i = 0, j = 0;
    while (i < N) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        
        if (j == M) {
            pos = i - j + 1; // Pattern found
            return true;
        } else if (i < N && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    return false;
}

/* 
 * Manacher's algorithm to find the longest palindrome in a given string.
 * @param s: input string
 * @param N: length of the input string
 * @param start: reference to store the starting position of the palindrome
 * @param end: reference to store the ending position of the palindrome
 */
void Manacher(char* s, int N, int& start, int& end) {
    int* P = new int[2 * N + 1]();
    char t[2 * N + 2];
    t[0] = '#';

    // Prepare the transformed string with '#' between characters
    for (int i = 0; i < N; i++) {
        t[2 * i + 1] = s[i];
        t[2 * i + 2] = '#';
    }
    t[2 * N + 1] = '\0';
    
    int C = 0, R = 0, maxLen = 0, center = 0;
    
    // Expand around center and calculate palindrome lengths
    for (int i = 1; i < 2 * N + 1; i++) {
        int mirr = 2 * C - i;
        if (i < R) P[i] = min(R - i, P[mirr]);
        else P[i] = 0;
        
        while (i + 1 + P[i] < 2 * N + 1 && i - 1 - P[i] >= 0 && t[i + 1 + P[i]] == t[i - 1 - P[i]]) {
            P[i]++;
        }
        
        if (i + P[i] > R) {
            C = i;
            R = i + P[i];
        }
        
        if (P[i] > maxLen) {
            maxLen = P[i];
            center = i;
        }
    }
    
    start = (center - maxLen) / 2 + 1;
    end = start + maxLen - 1;

    delete[] P;
}

/* 
 * Function to find the longest common substring between two strings using dynamic programming.
 * @param s1: first input string
 * @param s2: second input string
 * @param m: length of the first string
 * @param n: length of the second string
 * @param start: reference to store the start of the longest common substring
 * @param end: reference to store the end of the longest common substring
 */
void LongestCommonSubstring(char* s1, char* s2, int m, int n, int& start, int& end) {
    int** dp = new int*[m + 1];
    for (int i = 0; i <= m; i++) {
        dp[i] = new int[n + 1]();
    }

    int length = 0;

    // Build the DP table and find the longest common substring
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > length) {
                    length = dp[i][j];
                    start = i - length + 1;
                    end = i;
                }
            } else {
                dp[i][j] = 0;
            }
        }
    }

    // Free the dynamically allocated memory
    for (int i = 0; i <= m; i++) {
        delete[] dp[i];
    }
    delete[] dp;
}

int main() {
    // Variables to store transmission and malicious code data
    char transmission1[MAX_LEN] = {0};
    char transmission2[MAX_LEN] = {0};
    char mcode1[MAX_LEN] = {0};
    char mcode2[MAX_LEN] = {0};
    char mcode3[MAX_LEN] = {0};
    int pos;
    
    // Open files and read their contents
    ifstream file1("transmission1.txt"), file2("transmission2.txt");
    ifstream mcode_file1("mcode1.txt"), mcode_file2("mcode2.txt"), mcode_file3("mcode3.txt");

    // Check for file reading errors
    if (!file1.is_open() || !file2.is_open() || !mcode_file1.is_open() || !mcode_file2.is_open() || !mcode_file3.is_open()) {
        cout << "Error al abrir los archivos." << endl;
        return 1;
    }

    // Read the content of the files
    file1.read(transmission1, MAX_LEN);
    file2.read(transmission2, MAX_LEN);
    mcode_file1.read(mcode1, MAX_LEN);
    mcode_file2.read(mcode2, MAX_LEN);
    mcode_file3.read(mcode3, MAX_LEN);

    int N1 = strlen(transmission1);
    int N2 = strlen(transmission2);
    int M1 = strlen(mcode1);
    int M2 = strlen(mcode2);
    int M3 = strlen(mcode3);

    // Part 1: Search for patterns using KMP algorithm
    if (KMPSearch(transmission1, mcode1, N1, M1, pos)) {
        cout << "true " << pos << endl;
    } else {
        cout << "false" << endl;
    }
    
    if (KMPSearch(transmission1, mcode2, N1, M2, pos)) {
        cout << "true " << pos << endl;
    } else {
        cout << "false" << endl;
    }

    if (KMPSearch(transmission1, mcode3, N1, M3, pos)) {
        cout << "true " << pos << endl;
    } else {
        cout << "false" << endl;
    }

    if (KMPSearch(transmission2, mcode1, N2, M1, pos)) {
        cout << "true " << pos << endl;
    } else {
        cout << "false" << endl;
    }
    
    if (KMPSearch(transmission2, mcode2, N2, M2, pos)) {
        cout << "true " << pos << endl;
    } else {
        cout << "false" << endl;
    }

    if (KMPSearch(transmission2, mcode3, N2, M3, pos)) {
        cout << "true " << pos << endl;
    } else {
        cout << "false" << endl;
    }

    // Part 2: Find the longest palindrome using Manacher's algorithm
    int start1, end1, start2, end2;
    Manacher(transmission1, N1, start1, end1);
    Manacher(transmission2, N2, start2, end2);
    
    cout << start1 << " " << end1 << endl;
    cout << start2 << " " << end2 << endl;

    // Part 3: Longest common substring using dynamic programming
    int lcsStart, lcsEnd;
    LongestCommonSubstring(transmission1, transmission2, N1, N2, lcsStart, lcsEnd);
    
    cout << lcsStart << " " << lcsEnd << endl;

    return 0;
}
