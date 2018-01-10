#ifndef RADIXSORT_H
#define RADIXSORT_H

#include <algorithm>

int r_comparisons;

// performs counting sort on arr with respect to the digit/place represented by place
void rsort(int* arr, int size, int place)
{
    int i = 0;
    int result[size];
    int count[10] = {0}; // intializes all to zero

    // storing the occurence of each digit in count[]
    // Note (arr[i] / place) % 10 obtains digit at place
    for (; i < size; ++i) {
        ++count[(arr[i] / place) % 10];
    }

    // count[] now represents position
    // each index stores the sum of previous counts.
    for (i = 1; i < 10; ++i) {
        count[i] += count[i - 1];
    }

    // building result
    for (i = size - 1; i >= 0; --i) {
        result[--count[(arr[i] / place) % 10]] = arr[i];
    }

    // after copying, arr now contains sorted numbers according to current digit
    std::copy(result, result + size, arr);
}

int radix_sort(int* arr, int size, int max)
{
    // note: place represents 10^n where n is current digit
    for (int place = 1; max / place > 0; place *= 10) {
        rsort(arr, size, place);
    }
    return 0;
}

#endif // RADIXSORT_H
