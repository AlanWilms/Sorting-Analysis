#ifndef MERGESORT_H
#define MERGESORT_H

#include <stdio.h>
#include <stddef.h>

int m_comparisons = 0;

// Using the middle as a dividing line between two sorted halves, this fuction interleaves
// both halves to create one, continuous sorted array of elements between low and high
void merge(int* arr, int low, int middle, int high) {
    int l = low;
    int h = high;
    int m = middle + 1;
    int i = 0;

    // temp array of same size
    long temp[h - l + 1];

    // adds elements to temp array in sorted order
    while (l <= middle && m <= high) {
        ++m_comparisons;
        if(arr[l] <= arr[m])
            temp[i++] = arr[l++];
        else
            temp[i++] = arr[m++];
    }

    // fills the rest, if any
    while (l <= middle) {
        ++m_comparisons;
        temp[i++] = arr[l++];
    }

    // fills the rest, if any
    while (m <= high) {
        ++m_comparisons;
        temp[i++] = arr[m++];
    }

    // copy temp array into original
    for (size_t k = 0; k < high - low + 1; ++k) {
        arr[low + k] = temp[k];
    }
}

// Immediately called by merge_sort
// keeps track of upper and lower bound through passed parameters
// splits array in half logically and recursively calls sort on each part
// merges each half together at the end
void msort(int* arr, int low, int high) {
    if (low < high) {

        // calculates the middle
        int middle = low + (high - low) / 2;

        // calls sort recursively on both halves
        msort(arr, low, middle);
        msort(arr, middle + 1, high);

        // combines the halves
        merge(arr, low, middle, high);
    }
}

// Note: max is unused, passed just to match parameters needed for function pointer
int merge_sort(int* arr, int size, int max) {
    if (size > 0)
        msort(arr, 0, size - 1);
    return m_comparisons;
}

#endif // MERGESORT_H
