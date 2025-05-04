#include <iostream>
#include <cstdlib>
#include <chrono>
#include <cstring>
#include <fstream>

using namespace std;

void insertionSort(int arr[], int n) {
    for(int i = 1; i < n; i++) {
        int j = i - 1;
        int key = arr[i];
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int n) {
    for(int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for(int j = i + 1; j < n; j++) {
            if(arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (i != min_idx) {
            swap(arr[i], arr[min_idx]);
        }
    }
}

int main() {
    int arr[100000];
    int tempArr[100000];

    // Seed random number generator
    srand(time(0));
    for(int i = 0; i < 100000; i++) {
        arr[i] = rand() % 100000;
    }

    // Open CSV files for writing
    ofstream insertionSortFile("insertion_sort_times.csv");
    ofstream selectionSortFile("selection_sort_times.csv");

    if (!insertionSortFile || !selectionSortFile) {
        cerr << "Error opening files!" << endl;
        return 1;
    }

    // Write CSV headers
    insertionSortFile << "InputSize,TimeTaken\n";
    selectionSortFile << "InputSize,TimeTaken\n";

    for(int i = 100; i <= 100000; i += 100) {
        memcpy(tempArr, arr, sizeof(arr));
        auto start = chrono::high_resolution_clock::now();
        insertionSort(tempArr, i);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> diff = end - start;
        insertionSortFile << i << "," << diff.count() << "\n";
    }
    cout << "Insertion sort times saved to insertion_sort_times.csv" << "\n"<<flush;

    for(int i = 100; i <= 100000; i += 100) {
        memcpy(tempArr, arr, sizeof(arr));
        auto start = chrono::high_resolution_clock::now();
        selectionSort(tempArr, i);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> diff = end - start;
        selectionSortFile << i << "," << diff.count() << "\n";
    }
    cout << "Selection sort times saved to selection_sort_times.csv" << "\n"<<flush;

    insertionSortFile.close();
    selectionSortFile.close();

    return 0;
}
