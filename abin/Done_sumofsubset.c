/*To Implement Sum of subsets Problem using Backtracking Agorithm for the user entered input and then find the 
running time of implementation using time() function.*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void sumofsubset(int arr[], int size, int subset[], int target, int currentsum, int index){
    if(target==currentsum){
        printf("{ ");
        for(int i=0; i<size; i++){
            if(subset[i]!=0){
                printf("%d ", arr[i]);
            }
        }
        printf("}, ");
        return;
    }

    if(currentsum>target || index>=size){
        return;
    }

    subset[index] = arr[index];
    sumofsubset(arr,size,subset,target,currentsum+arr[index],index+1);

    subset[index] = 0;
    sumofsubset(arr,size,subset,target,currentsum,index+1);
}

int main()
{
    int n, target;
    printf("Enter the number of elements in set: ");
    scanf("%d", &n);
    int arr[n], subset[n];
    for(int i=0; i<n; i++){
        subset[i] = 0;
    }
    printf("Enter the elements in set:\n");
    for(int i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }
    printf("Enter target sum: ");
    scanf("%d", &target);

    printf("Subsets with sum %d are:\n", target);
    clock_t start = clock();
    sumofsubset(arr,n,subset,target,0,0);
    clock_t end = clock();

    printf("Time taken: %f miliseconds", 1000*(double)(end-start)/CLOCKS_PER_SEC);
    return 0;
}
