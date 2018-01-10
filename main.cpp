// CS 3250 Extra Credit
// Alan Wilms
// VUNetID: wilmsa
// Email: alan.wilms@vanderbilt.edu
// Honor Code: I have neither given nor received unauthorized aid.

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <utility>
#include <cstdio>
#include <ctime>
#include <chrono>
#include "mergesort.h"
#include "quicksort.h"
#include "radixsort.h"

int count = 0;
int max = 0;
char in = ' ';
bool print_flag = false;

int* initialize() {

    std::cout << "This is an analysis of sorting algorithms." << std::endl;
    std::cout << "Would you like to generate your own numbers? \n1: File input\n2: User input\n3: Randomized input\n(Type 1, 2, or 3): ";
    while (!(std::cin >> in && (tolower(in) == '1' || tolower(in) == '2' || tolower(in) == '3'))) {
        std::cout << "Invalid character. Please try again: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "How many numbers? ";
    while (!(std::cin >> count && count > 0)) {
        std::cout << "Invalid number. Please try again: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    int* input = new int[count]();
    std::cout << "Maxmimum value? ";
    while (!(std::cin >> max && max > 0)) {
        std::cout << "Invalid number. Please try again: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if (in == '2') {
        std::cout << "Please enter the numbers separated by spaces (or new lines):" << std::endl;
        bool flag = true;
        do {
            if (flag == false) { // resetting flag
                std::cout << "Invalid sequence of numbers. Please try again: " << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                flag = true;
            }
            for (int i = 0; i < count; ++i) {
                if (!(std::cin >> input[i] && input[i] <= max)) {
                    flag = false;
                    break;
                }
            }
        } while(!flag);
    } else if (in == '3') {
        std::srand(time(NULL));
        for (int i = 0; i < count; ++i) {
            input[i] = rand() % (max + 1);
        }
    } else {
        std::cout << "Please enter the file name: ";
        std::string file_name;
        while (!(std::cin >> file_name)) {
            std::cout << "File name. Please try again: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Opening " << file_name << ". . ." << std::endl;
        std::ifstream file(file_name);
        if(file.is_open()) {
            for(int i = 0; i < count; ++i) {
                if (!(file >> input[i])) {
                    throw std::exception();
                }
            }
        } else {
            throw std::exception();
        }
    }
    return input;
}

void print(std::string label, int* arr) {
    std::cout << label;
    std::copy(arr, arr + count, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

double time(int* arr, int (*f)(int*, int, int)) {
    // std::clock_t start = std::clock();
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    std:: cout << "Number of comparisons: " << (*f)(arr, count, max) << std::endl;
    std::chrono::high_resolution_clock::time_point finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start);
    // float duration = (float)(1000 * (std::clock() - start)) / (float)CLOCKS_PER_SEC;
    double duration = 1000*time_span.count();
    std::cout<<"Time: "<< duration << " ms" << std::endl;
    return duration;
}

int main() {
    int* a = initialize();
    int* b = new int[count]();
    int* c = new int[count]();
    std::copy(a, a + count, b);
    std::copy(a, a + count, c);

    if (print_flag) print("Unsorted: ", a);

    std::cout << "-~-~-~-~-MergeSort-~-~-~-~-" << std::endl;
    time(a, merge_sort);
    if (print_flag) print("Sorted:   ", a);

    std::cout << "-~-~-~-~-QuickSort-~-~-~-~-" << std::endl;
    time(b, quick_sort);
    if (print_flag) print("Sorted:   ", b);

    std::cout << "-~-~-~-~-RadixSort-~-~-~-~-" << std::endl;
    time(c, radix_sort);
    if (print_flag) print("Sorted:   ", c);

    // for the creation of a descending order input
    // std::sort(a, a + count, std::greater<int>());

    std::ofstream myfile("output.txt");
    if (myfile.is_open()) {
        for (int i = 0; i < count; ++i) {
            myfile << a[i] << " ";
        }
        myfile.close();
    }
    else std::cout << "Unable to open file." << std::endl;

    delete[] a;
    delete[] b;
    delete[] c;
    return 0;
}
