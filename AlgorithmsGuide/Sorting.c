// Sorting Algorithms as part of the COMP2521 - 2022 - T3 curriculum
// Sorting pseudocode taken from COMP2521 - 2022 -T3 lecture slides
// Sorting Arrays

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Sorting.h"

int Partition(int *arr, int lo, int hi);
void Swap(int *a, int *b);

void SelectionSort(int *arr, int arrSize) {
    int i, j, min;
    for (i = 0; i < arrSize - 1; i++) {
        min = i;
        for (j = i + 1; j < arrSize; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        Swap(&arr[i], &arr[min]);
    }
}

void BubbleSort(int *arr, int arrSize) {
    int i, j;
    bool isSorted = true;
    for (i = 0; i < arrSize; i++) {
        for (j = arrSize - 1; j > i; j--) {
            if (arr[j] < arr[j - 1]) {
                Swap(&arr[j], &arr[j - 1]);
                isSorted = false;
            }
        }
        if (isSorted) {
            break;
        }
    }
}

void InsertionSort(int *arr, int arrSize) {
    int i, j, temp;
    for (i = 1; i < arrSize; i++) {
        temp = arr[i];
        for (j = i; j > 0; j--) {
            if (temp < arr[j-1]) {
                arr[j] = arr[j-1];
            } else break;
        }
        arr[j] = temp;
    }
}

// QuickSort(arr, 0, ARR_SIZE - 1);
void QuickSort(int *arr, int lo, int hi) {
    int i;
    if (lo >= hi) {
        return;
    }
    i = Partition(arr, lo, hi);
    QuickSort(arr, lo, i - 1);
    QuickSort(arr, i + 1, hi);
}




// Helpers

int Partition(int *arr, int lo, int hi) {
    int pivot = arr[hi];
    int i = lo - 1;
    for (int j = lo; j <= hi - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            Swap(&arr[i], &arr[j]);
        }
    }
    Swap(&arr[i + 1], &arr[hi]);
    return (i + 1);   
}

void Swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
