#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high){
    int pivot = arr[low];
    int i = low - 1;
    int j = high + 1;

    while(1){
        do{
            j--;
        }while(arr[j] > pivot);
        
        do{
            i++;
        }while(arr[i] < pivot);

        if(i < j){
            swap(&arr[i], &arr[j]);
        }
        else{
            return j;
        }
    }
}

void quickSort(int arr[], int low, int high){
    if(low < high){
        int pivot = partition(arr,low,high);
        quickSort(arr, low, pivot);
        quickSort(arr, pivot+1, high);
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
    quickSort(arr, 0, n-1);
    clock_t end1 = clock();
    printf("Sorted array using Quick Sort: ");
    printArray(arr,n);
    printf("\nTime taken by quick sort: %f seconds\n", (double)(end1-start1)/CLOCKS_PER_SEC);
}
