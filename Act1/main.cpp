/*
    Program that implements the merge sort algorithm to sort an array of decimal numbers in descending order.
    Author: Diego Ivan Morales Gallardo
    Creation Date: August 16, 2024
    General Complexity: The overall complexity of the merge sort algorithm is O(n log n), where n is the number of elements in the array.
*/

#include <iostream>

/*
    Function that merges two sorted subarrays into one sorted subarray.
    Parameters:
    - numbers[]: Array of decimal numbers being sorted.
    - left: Starting index of the subarray to be sorted.
    - mid: Middle index that divides the subarray into two halves.
    - right: Ending index of the subarray to be sorted.
    Complexity: The complexity of this merge function is O(n), where n is the total number of elements in the two subarrays.
*/
void merge(double numbers[], int left, int mid, int right) {
    int sizeLeft = mid - left + 1;
    int sizeRight = right - mid;
    double* leftArr = new double[sizeLeft];
    double* rightArr = new double[sizeRight];

    for (int leftIndex = 0; leftIndex < sizeLeft; ++leftIndex) {
        leftArr[leftIndex] = numbers[left + leftIndex];
    }

    for (int rightIndex = 0; rightIndex < sizeRight; ++rightIndex) {
        rightArr[rightIndex] = numbers[mid + 1 + rightIndex];
    }

    int leftIndex = 0, rightIndex = 0, mergeIndex = left;

    while (leftIndex < sizeLeft && rightIndex < sizeRight) {
        if (leftArr[leftIndex] >= rightArr[rightIndex]) {
            numbers[mergeIndex++] = leftArr[leftIndex++];
        } else {
            numbers[mergeIndex++] = rightArr[rightIndex++];
        }
    }

    while (leftIndex < sizeLeft) {
        numbers[mergeIndex++] = leftArr[leftIndex++];
    }

    while (rightIndex < sizeRight) {
        numbers[mergeIndex++] = rightArr[rightIndex++];
    }

    delete[] leftArr;
    delete[] rightArr;
}

/*
    Recursive function that applies the merge sort algorithm to an array of decimal numbers.
    Parameters:
    - numbers[]: Array of decimal numbers to be sorted.
    - left: Starting index of the subarray to be sorted.
    - right: Ending index of the subarray to be sorted.
    Complexity: The complexity of this mergeSort function is O(n log n), where n is the number of elements in the array.
*/
void mergeSort(double numbers[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(numbers, left, mid);
        mergeSort(numbers, mid + 1, right);
        merge(numbers, left, mid, right);
    }
}

int main() {
    int numElements;
    std::cin >> numElements;
    double* numbers = new double[numElements];

    for (int i = 0; i < numElements; ++i) {
        std::cin >> numbers[i];
    }

    mergeSort(numbers, 0, numElements - 1);

    for (int i = 0; i < numElements; ++i) {
        std::cout << numbers[i] << std::endl;
    }

    delete[] numbers;
    return 0;
}
