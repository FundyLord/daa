/*To Implement Insertion sort and Selection sort for the user entered input and then find the running time of 
implementation using time() function. */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void insertionSort(int arr[], int n)
{
    for(int j=1; j<n; j++)
    {
        int key = arr[j];
        int i = j-1;
        while (i>=0 && arr[i]>key)
        {
            arr[i+1] = arr[i];
            i=i-1;
        }
        arr[i+1] = key;
    }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        int temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}

void printarray(int arr[], int n)
{
    for(int i=0; i<n; i++)
    {
        printf("%d ",arr[i]);
    }
}

int main()
{
    int n;
    printf("Enter total count of number to be taken as input: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter Numbers: ");
    for(int i=0; i<n; i++)
    {
        scanf("%d",&arr[i]);
    }

    clock_t start1 = clock();
    insertionSort(arr,n);
    clock_t end1 = clock();
    printf("sorted array using insertion sort: ");
    printarray(arr,n);
    printf("\nTime taken: %f seconds\n",(end1-start1)/CLOCKS_PER_SEC);

    clock_t start2 = clock();
    selectionSort(arr,n);
    clock_t end2 = clock();
    printf("sorted array using selection sort: ");
    printarray(arr,n);
    printf("\nTime taken: %f seconds\n",(end2-start2)/CLOCKS_PER_SEC);
    return 0;
}

/*srand(time(0));
    for(int i = 0; i < n; i++) {
        arr[i] = rand() % n;
    }
*/
