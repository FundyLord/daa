// C Program for Maximum Subarray Sum using Kadane's Algorithm

#include <stdio.h>
#include <limits.h>

// Function to find the maximum subarray sum
int maxSubarraySum(int arr[], int size) {
    int res = arr[0];
    int maxEnding = arr[0];

    for (int i = 1; i < size; i++) {
        
        // Find the maximum sum ending at index i by either extending 
        // the maximum sum subarray ending at index i - 1 or by
        // starting a new subarray from index i
        maxEnding = (maxEnding + arr[i] > arr[i]) ? 
          									maxEnding + arr[i] : arr[i];
      
        // Update res if maximum subarray sum ending at index i > res
        res = (res > maxEnding) ? res : maxEnding;
    }
    return res;
}

int main() {
    int arr[] = {2, 3, -8, 7, -1, 2, 3};
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("%lld\n", maxSubarraySum(arr, size));
    return 0;
}
















// 1) Input:
// - An array of integers (arr[]) of size 'size'
// - Can contain positive, negative, or zero values

// 2) Algorithm:
// Kadane's Algorithm:
// - Traverse array once
// - At each element, decide:
//   a) Extend current subarray
//   b) Start new subarray
// - Track maximum subarray sum found so far

// 3) Time Complexity:
// Best/Avg/Worst Case: O(n), where n = size of array
// Single pass through array

// 4) Space Complexity:
// - O(1), constant extra space used

// 5) Advantages / Disadvantages:
// + Very efficient with linear time
// + Simple to implement
// - Only gives sum, not the actual subarray
// - Doesn't handle all-negative arrays gracefully unless modified

// 6) Recurrence Relation:
// maxEnding[i] = max(arr[i], maxEnding[i-1] + arr[i])
// res = max(res, maxEnding[i])

// 7) Summary (2 lines):
// Finds maximum sum of contiguous subarray in O(n) time.
// Efficient and simple, ideal for large input sizes.