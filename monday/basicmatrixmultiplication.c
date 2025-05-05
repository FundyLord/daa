#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
//bottum-up approach


// Function to return the minimum number of multiplications
int matrixMultiplication(int arr[], int n) {
    // Create 2D DP array (n x n)
    int** dp = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        dp[i] = (int*)malloc(n * sizeof(int));
    }

    // Initialize DP table
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = 0;
        }
    }

    // Fill the DP table in bottom-up manner
    for (int len = 2; len < n; len++) { // length of subchain
        for (int i = 0; i < n - len; i++) {
            int j = i + len;
            dp[i][j] = INT_MAX;

            // Try placing parenthesis at different positions
            for (int k = i + 1; k < j; k++) {
                int cost = dp[i][k] + dp[k][j] + arr[i] * arr[k] * arr[j];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                }
            }
        }
    }

    // Minimum cost to multiply entire chain
    int result = dp[0][n - 1];

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

// Driver program
int main() {
    int arr[] = {2, 1, 3, 4}; // Dimensions: M1(2x1), M2(1x3), M3(3x4)
    int n = sizeof(arr) / sizeof(arr[0]);

    int minMult = matrixMultiplication(arr, n);

    printf("Minimum number of multiplications: %d\n", minMult);

    return 0;
}


//top-down approach
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

// Global memoization table
int** memo;

// Function to print 2D memo table (optional)
void printMemoTable(int n) {
    printf("\nMemo Table:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (memo[i][j] == -1)
                printf("  - ");
            else
                printf("%3d ", memo[i][j]);
        }
        printf("\n");
    }
}

// Recursive function with memoization
int matrixChainRecursive(int arr[], int i, int j) {
    // Base case: only one matrix
    if (i == j)
        return 0;

    // If already computed
    if (memo[i][j] != -1)
        return memo[i][j];

    // Initialize minimum cost
    memo[i][j] = INT_MAX;

    // Try placing parenthesis at all possible positions
    for (int k = i + 1; k < j; k++) {
        int left = matrixChainRecursive(arr, i, k);
        int right = matrixChainRecursive(arr, k, j);
        int cost = left + right + arr[i] * arr[k] * arr[j];

        if (cost < memo[i][j])
            memo[i][j] = cost;
    }

    return memo[i][j];
}

// Wrapper function to initialize memoization table
int matrixMultiplicationTopDown(int arr[], int n) {
    // Allocate memoization table
    memo = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        memo[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
            memo[i][j] = -1; // -1 means not computed yet
    }

    // Call recursive function
    int result = matrixChainRecursive(arr, 0, n - 1);

    // Free memo table
    for (int i = 0; i < n; i++) {
        free(memo[i]);
    }
    free(memo);

    return result;
}

// Utility function to generate random power-of-two dimensions
void generateRandomDimensions(int arr[], int size) {
    srand(time(NULL));
    arr[0] = pow(2, rand() % 6 + 3); // Between 8 and 128

    for (int i = 1; i <= size; i++) {
        arr[i] = pow(2, rand() % 6 + 3);
    }
}
// void printOptimalParens(int s[][10], int i, int j) {
//     if (i == j)
//         printf("A%d", i);
//     else {
//         printf("(");
//         printOptimalParens(s, i, s[i][j]);
//         printOptimalParens(s, s[i][j] + 1, j);
//         printf(")");
//     }
// }

// Function to print worst-case time complexity
void printTimeComplexity(int n, const char* method) {
    printf("Worst Case Time Complexity for %s with n = %d: O(2^n)\n", method, n);
    printf("With memoization: O(n^3)\n");
}

// Driver program
int main() {
    int choice, n;

    printf("Choose input type:\n");
    printf("1. Use default input [2, 1, 3, 4]\n");
    printf("2. Generate random dimensions\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        int arr[] = {2, 1, 3, 4};
        n = sizeof(arr) / sizeof(arr[0]);

        printf("Input Dimensions: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        int minMult = matrixMultiplicationTopDown(arr, n);
        printf("Minimum number of multiplications: %d\n", minMult);
        printTimeComplexity(n, "Top-Down Recursive DP");
    } else if (choice == 2) {
        int maxMatrices;
        printf("Enter number of matrices: ");
        scanf("%d", &maxMatrices);
        n = maxMatrices + 1;
        int* arr = (int*)malloc(n * sizeof(int));

        generateRandomDimensions(arr, maxMatrices);

        printf("Generated Dimensions: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        int minMult = matrixMultiplicationTopDown(arr, n);
        printf("Minimum number of multiplications: %d\n", minMult);
        printTimeComplexity(n, "Top-Down Recursive DP");

        free(arr);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}














// 1) Input:
// - arr[]: Array of matrix dimensions (size = n)
//   For matrices M1(p×q), M2(q×r), ..., Mn(r×s), arr = [p, q, r, ..., s]
// - n: Number of elements in arr = number of matrices + 1

// 2) Algorithm:
// Bottom-Up DP:
// - Fill dp[i][j] for all subchains from length 2 to n-1
// - Try all possible k between i and j for optimal split
// Top-Down Memoized Recursion:
// - Recursive function with memo table
// - Avoid recomputation using stored values

// 3) Time Complexity:
// Best Case: O(n^3) due to triple nested loops
// Worst/Avg Case: O(n^3) – polynomial but high cubic growth
// Without memoization: O(2^n) exponential recursion

// 4) Advantages / Disadvantages:
// + Bottom-up uses less stack space, faster constant factors
// + Top-down intuitive and easy to debug
// - High memory usage (O(n^2) for DP tables)
// - Not scalable for large n (>100)

// 5) Recurrence Relation:
// M(i, j) = min{ M(i,k) + M(k,j) + arr[i]*arr[k]*arr[j] }, for i < k < j
// Base case: M(i,i) = 0

// 6) Formula Used:
// Cost to multiply A[p×q] × B[q×r] = p × q × r scalar multiplications

// 7) Summary (2 lines):
// Solves matrix chain multiplication via bottom-up DP and top-down memoization.
// Efficient for moderate sizes; becomes heavy for large chains due to cubic time.