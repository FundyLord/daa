#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include<limits.h>
// #include<0>
#define MAX 10

typedef struct
{
    int low;
    int high;
    int sum;
} Set;

Set *FindMaxCrossingSubArray(int arr[], int low, int mid, int high)
{
    int leftSum = INT_MIN, rightSum = 0, sum = 0;
    int leftMax, rightMax;
    int i, j;
    for (i = mid; i >= low; i--)
    {
        sum = sum + arr[i];
        if (sum > leftSum)
        {
            leftSum = sum;
            leftMax = i;
        }
    }
    rightMax = 0;
    rightSum = INT_MIN;
    sum = 0;
    for (j = mid + 1; j <= high; j++)
    {
        sum = sum + arr[j];
        if (sum > rightSum)
        {
            rightSum = sum;
            rightMax = j;
        }
    }

    Set * ans = (Set*)malloc(sizeof(Set));
    ans->low = leftMax;
    ans->high = rightMax;
    ans->sum = leftSum+rightSum;

    return ans;
}

Set *FindMaximumSubArray(int arr[], int low, int high)
{
    int mid;

    if (low == high)
    {
        Set *singleElement = (Set *)malloc(sizeof(Set));
        singleElement->low = low;
        singleElement->high = high;
        singleElement->sum = arr[low];
        return singleElement;
    }
    else
    {
        mid = (low+high)/2;
        Set *left = FindMaximumSubArray(arr, low, mid);

        Set *middle = FindMaxCrossingSubArray(arr, low, mid, high);

        Set *right = FindMaximumSubArray(arr, mid + 1, high);
        
        if (left->sum >= right->sum && left->sum >=middle->sum)
            return left;
        else if (right->sum >= left->sum && right->sum >= middle->sum)
            return right;
        else
            return middle;
    }
}
void displayWithIndex(int arr[],int n)
{
    int i;
    for (int i = 0; i < n; i++)
    {
        printf("arr[%d] = %d\n",i,arr[i]);
    }
}
int main(int argc, char const *argv[])
{
    int arr[] = {-13, -3, -25, -20, -3, -16, -23, -18, -20, -7, -12, -5, -22, -15, -4, -7};
    // int arr[] = {-8, -3, -6, -2, -5, -4};

    int n = sizeof(arr) / sizeof(int);
    displayWithIndex(arr,n);
    Set *result = FindMaximumSubArray(arr, 0, n-1);
    printf("Max Sub array is from index %d [%d] to %d [%d] with sum of %d\n",result->low,arr[result->low],result->high,arr[result->high],result->sum);
    return 0;
}
