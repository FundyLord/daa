#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int arr[], int p, int q, int r);

void mergeSort(int arr[], int p, int r){
    if(p<r){
        int q = (p+r)/2;
        mergeSort(arr, p, q);
        mergeSort(arr, q+1, r);
        merge(arr, p, q, r);
    }
}

void merge(int arr[], int p, int q, int r){
    int n1 = q - p + 1;
    int n2 = r - q;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[p + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[q + 1 + j];
    }

    int i = 0, j = 0, k = p;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }

    while (j < n2) {
        arr[k++] = R[j++];
    }
}


void printArray(int arr[], int n){
    for(int i=0; i<n; i++){
        printf("%d ", arr[i]);
    }
}

int main(){
    int n;
    printf("Enter the total count of number to be taken as input: ");
    scanf("%d", &n);
    int arr[n];
    srand(time(0));
    for(int i = 0; i < n; i++) {
        arr[i] = rand() % n;
    }
    printf("Unsorted array:\n");
    printArray(arr,n);
    printf("\n\n");
    

    clock_t start1 = clock();
    mergeSort(arr, 0, n-1);
    clock_t end1 = clock();
    printf("Sorted array using Merge Sort: ");
    printArray(arr,n);
    printf("\nTime taken by merge sort: %f seconds\n", (double)(end1-start1)/CLOCKS_PER_SEC);
}
