#include <stdio.h>
#include <limits.h>

// Function to find maximum in three numbers
int max(int a, int b, int c) {
    return (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
}

// Function to find maximum crossing subarray that includes mid
int maxCrossingSum(int arr[], int left, int mid, int right) {
    // Include at least one element from each side
    int sum = 0;
    int leftSum = INT_MIN;

    // Left part of the subarray
    for (int i = mid; i >= left; i--) {
        sum += arr[i];
        if (sum > leftSum)
            leftSum = sum;
    }

    sum = 0;
    int rightSum = INT_MIN;

    // Right part of the subarray
    for (int i = mid + 1; i <= right; i++) {
        sum += arr[i];
        if (sum > rightSum)
            rightSum = sum;
    }

    // Return sum of elements on left and right including mid
    return leftSum + rightSum;
}

// Main function to find maximum subarray sum using divide and conquer
int maxSubArraySum(int arr[], int left, int right) {
    // Base Case: Only one element
    if (left == right)
        return arr[left];

    int mid = (left + right) / 2;

    // Recursively get maximum values from left, right, and crossing subarrays
    int leftMax = maxSubArraySum(arr, left, mid);
    int rightMax = maxSubArraySum(arr, mid + 1, right);
    int crossMax = maxCrossingSum(arr, left, mid, right);

    return max(leftMax, rightMax, crossMax);
}

// Wrapper function to simplify interface
int maxSubarray(int arr[], int n) {
    return maxSubArraySum(arr, 0, n - 1);
}

// Driver program
int main() {
    int arr[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int n = sizeof(arr) / sizeof(arr[0]);

    int max_sum = maxSubarray(arr, n);

    printf("Maximum subarray sum is %d\n", max_sum);

    return 0;
}
























// 1) Input:
// - An array of integers (arr[]) of size 'n'

// 2) Algorithm:
// Divide and Conquer approach:
// - Divide array into two halves
// - Recursively find max subarray in left, right, and crossing mid
// - Combine results by taking maximum of the three

// 3) Time Complexity:
// Best/Avg/Worst Case: O(n log n)
// Each level processes O(n) elements, and recursion depth is O(log n)

// 4) Space Complexity:
// - O(log n), due to recursion stack
// - No additional memory used beyond call stack

// 5) Advantages / Disadvantages:
// + Better theoretical time complexity than naive O(n^2) methods
// + Good parallelization potential
// - Slower in practice than Kadane’s algorithm due to overhead
// - More complex than linear scan solution

// 6) Recurrence Relation:
// T(n) = 2T(n/2) + O(n), where O(n) is for computing crossing sum
// Solves to T(n) = O(n log n)

// 7) Summary (2 lines):
// Finds maximum subarray sum using divide and conquer strategy.
// Efficient but not as fast as Kadane’s algorithm for large arrays.