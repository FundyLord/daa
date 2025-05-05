#include <stdio.h>
#include <stdlib.h>

// Global variables
int max_value = 0;

// Utility function to swap elements (used for sorting)
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Sort items by value/weight ratio (optional greedy optimization)
void sortItems(int weights[], int values[], int n) {
    double ratio[n];
    for (int i = 0; i < n; i++) {
        ratio[i] = (double)values[i] / weights[i];
    }

    // Simple bubble sort based on ratio
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (ratio[j] < ratio[j + 1]) {
                swap(&weights[j], &weights[j + 1]);
                swap(&values[j], &values[j + 1]);
                swap(&ratio[j], &ratio[j + 1]);
            }
        }
    }
}

// Recursive backtracking function
void backtrack(int weights[], int values[], int n, int index, int currentWeight, int currentValue, int W) {
    // Base case: if we've processed all items
    if (index == n) {
        if (currentValue > max_value) {
            max_value = currentValue;
        }
        return;
    }

    // Prune path if already over capacity
    if (currentWeight > W)
        return;

    // Option 1: Include current item
    backtrack(weights, values, n, index + 1,
              currentWeight + weights[index],
              currentValue + values[index],
              W);

    // Option 2: Exclude current item
    backtrack(weights, values, n, index + 1,
              currentWeight,
              currentValue,
              W);
}

// Main function to call backtracking
int knapsackBacktracking(int weights[], int values[], int n, int W) {
    // Optional: Sort items by value/weight to improve pruning
    sortItems(weights, values, n);

    backtrack(weights, values, n, 0, 0, 0, W);
    return max_value;
}

// Driver program
int main() {
    int n, W;

    printf("Enter number of items: ");
    scanf("%d", &n);

    int* weights = (int*)malloc(n * sizeof(int));
    int* values = (int*)malloc(n * sizeof(int));

    printf("Enter maximum capacity of knapsack: ");
    scanf("%d", &W);

    printf("Enter weight and value for each item:\n");
    for (int i = 0; i < n; i++) {
        printf("Item %d\n", i + 1);
        printf("Weight: ");
        scanf("%d", &weights[i]);
        printf("Value: ");
        scanf("%d", &values[i]);
        printf("\n");
    }

    int result = knapsackBacktracking(weights, values, n, W);

    printf("Maximum value that can be put in knapsack: %d\n", result);

    free(weights);
    free(values);

    return 0;
}


























// 1) Input:
// - weights[]: Array of item weights
// - values[]: Array of item values
// - n: Number of items
// - W: Maximum weight capacity of knapsack

// 2) Algorithm:
// Recursive backtracking with pruning:
// - At each step, choose to include or exclude current item
// - Prune paths where weight exceeds capacity
// - Optional greedy optimization: sort by value/weight ratio

// 3) Time Complexity:
// Best Case: O(n log n) — if all items fit and sorted only
// Worst Case: O(2^n) — trying all subsets
// Average Case: Still exponential unless pruning is effective

// 4) Space Complexity:
// - O(n), due to recursion stack depth
// - O(n) additional space for input arrays and ratios

// 5) Advantages / Disadvantages:
// + Guaranteed correct solution (brute-force complete)
// + Simple to implement and understand
// - Very slow for large n (n > 20 not feasible)
// - No dynamic programming reuse of subproblems

// 6) Recurrence Relation:
// T(n) = T(n-1, W) + T(n-1, W-w[n]) + O(1)
// Base case: T(0, *) = 0

// 7) Summary (2 lines):
// Solves 0/1 Knapsack using recursive backtracking with pruning.
// Exact but exponential — suitable for small input sizes.