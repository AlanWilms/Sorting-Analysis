#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <algorithm>

int q_comparisons = 0;

// Takes random element as pivot to reduce worst case performance, places the pivot element at its
// correct position in the sorted array
int partition (int* arr, int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        // checks if current element is smaller than or equal to pivot
        ++q_comparisons;
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    // moves pivot to the correct location
    std::swap(arr[++i], arr[high]);
    return i;
}

// Immediately called by quick_sort
// keeps track of upper and lower bound through passed parameters
// splits array in half by pivot element and recursively calls sort on each part
// the pivot element is in the correct location
void qsort(int* arr, int low, int high)
{
    if (low < high) {
        int part = partition(arr, low, high);
        // two recursive calls, one on each side of the partition
        qsort(arr, low, part - 1);
        qsort(arr, part + 1, high);
    }
}

// Note: max is unused, passed just to match parameters needed for function pointer
int quick_sort(int *arr, int size, int max) {
    if (size > 0)
        qsort(arr, 0, size - 1);
    return q_comparisons;
}

#endif // QUICKSORT_H
