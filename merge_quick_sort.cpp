#include <iostream>
#include <cstdlib>
#include <chrono>
#include <cstring>
#include <fstream>
using namespace std;

void merge(int arr[], int low, int mid, int high) {
    int temp[high - low + 1]; // Temporary array
    int left = low, right = mid + 1, k = 0;

    // Merge the two halves
    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) {
            temp[k++] = arr[left++];
        } else {
            temp[k++] = arr[right++];
        }
    }

    // Copy remaining elements from the left half
    while (left <= mid) {
        temp[k++] = arr[left++];
    }

    // Copy remaining elements from the right half
    while (right <= high) {
        temp[k++] = arr[right++];
    }

    // Copy sorted elements back to original array
    for (int i = 0; i < k; i++) {
        arr[low + i] = temp[i];
    }
}


void mergeSort(int arr[], int low, int high) {
    if(low>=high) return;
    int mid = (low+high)/2;
    //left half
    mergeSort(arr,low,mid);
    //right half
    mergeSort(arr,mid+1,high);
    merge(arr,low,mid,high);
}

int partition(int arr[], int low, int high) {
    int pivot = arr[low];
    int i = low;
    int j = high;
    while(i<j) {
        while(arr[i]<=pivot && i<=high-1) {
            i++;
        }
        while(arr[j]>pivot && j>=low+1) {
            j--;    
        }
        if(i<j) swap(arr[i],arr[j]);
    }
    swap(arr[low],arr[j]);
    return j;
}


void qs(int arr[], int low, int high) {
    if(low<high) {
        int pIndex = partition(arr,low,high);
        qs(arr,low,pIndex-1);
        qs(arr,pIndex+1,high);
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
    ofstream mergeQuickSortFile("merge_quick_sort_times.csv");

    if (!mergeQuickSortFile) {
        cerr << "Error opening files!" << endl;
        return 1;
    }

    // Write CSV headers
    mergeQuickSortFile << "InputSize,TimeTakenMerge,TimeTakeQuick\n";

    for(int i = 100; i <= 100000; i += 100) {
        memcpy(tempArr, arr, sizeof(arr));
        auto start = chrono::high_resolution_clock::now();
        mergeSort(tempArr,0, i);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> diff1 = end - start;
        memcpy(tempArr, arr, sizeof(arr));
        start = chrono::high_resolution_clock::now();
        qs(tempArr,0,i);
        end = chrono::high_resolution_clock::now();
        chrono::duration<double> diff2 = end - start;
        cout << i << "," << diff1.count()<< ","<<diff2.count() << "\n";
        mergeQuickSortFile << i << "," << diff1.count()<< ","<<diff2.count() << "\n";
    }
    cout << "merge sort times saved to merge_quick_sort_times.csv" << "\n"<<flush;
    mergeQuickSortFile.close();

    return 0;
}
