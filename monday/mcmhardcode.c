#include <stdio.h>
#include <limits.h>

#define MAX 100

void printOptimalParenthesis(int s[MAX][MAX], int i, int j) {
    if (i == j)
        printf("A%d", i);
    else {
        printf("(");
        printOptimalParenthesis(s, i, s[i][j]);
        printOptimalParenthesis(s, s[i][j] + 1, j);
        printf(")");
    }
}

void matrixChainOrderBottomUp(int p[], int n) {
    int m[MAX][MAX];  // m[i][j] = min cost to multiply Ai...Aj
    int s[MAX][MAX];  // s[i][j] = best split k

    for (int i = 1; i <= n; i++)
        m[i][i] = 0;

    for (int L = 2; L <= n; L++) {
        for (int i = 1; i <= n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = INT_MAX;

            for (int k = i; k < j; k++) {
                int cost = m[i][k] + m[k+1][j] + p[i-1] * p[k] * p[j];
                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }

    printf("Minimum number of multiplications (Bottom-Up): %d\n", m[1][n]);
    printf("Optimal Parenthesization: ");
    printOptimalParenthesis(s, 1, n);
    printf("\n");
}



int memo[MAX][MAX];  // Memoization table
int splits[MAX][MAX];  // To store split points

int matrixChainMemoized(int p[], int i, int j, int memo[][MAX], int splits[][MAX]) {
    if (i == j) {
        return 0;
    }

    if (memo[i][j] != -1)
        return memo[i][j];

    int minCost = INT_MAX;

    for (int k = i; k < j; k++) {
        int cost = matrixChainMemoized(p, i, k, memo, splits) +
                   matrixChainMemoized(p, k + 1, j, memo, splits) +
                   p[i - 1] * p[k] * p[j];

        if (cost < minCost) {
            minCost = cost;
            splits[i][j] = k;
        }
    }

    memo[i][j] = minCost;
    return minCost;
}

void matrixChainOrderTopDown(int p[], int n) {
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++) {
            memo[i][j] = -1;
            splits[i][j] = 0;
        }

    int minMult = matrixChainMemoized(p, 1, n, memo, splits);

    printf("Minimum number of multiplications (Top-Down): %d\n", minMult);
    printf("Optimal Parenthesization: ");
    printOptimalParenthesis(splits, 1, n);
    printf("\n");  
}




int main() {
    int p[] = {5, 10, 3, 12, 5};  
    int n = sizeof(p) / sizeof(p[0]) - 1;  

    printf("=== Bottom-Up DP ===\n");
    matrixChainOrderBottomUp(p, n);

    printf("\n=== Top-Down DP ===\n");
    matrixChainOrderTopDown(p, n);

    return 0;
}


// 1) Input:
// - arr[]: Array of matrix dimensions (size = n)
//   For matrices M1(p×q), M2(q×r), ..., Mn(r×s), arr = [p, q, r, ..., s]
// - n: Number of elements in arr = number of matrices + 1

// 2) Algorithm:
// Bottom-Up DP:
// - Fill dp[i][j] for all subchains from length 2 to n-1
// - Try placing parenthesis at all possible k positions
// Top-Down Memoized Recursion:
// - Recursive function with memo table
// - Avoid recomputation using stored values

// 3) Time Complexity:
// Best/Avg/Worst Case: O(n^3) due to triple nested loops
// Without memoization: O(2^n) exponential recursion

// 4) Space Complexity:
// - O(n^2), for DP or memo tables
// - Additional stack space for recursive calls (top-down)

// 5) Advantages / Disadvantages:
// Bottom-Up:
// + Faster constant factors, no recursion overhead
// + Predictable memory usage
// - Less intuitive than top-down
// Top-Down:
// + Easier to implement and understand
// + Natural expression of recurrence
// - Higher memory overhead from recursion stack
// Both:
// - Not scalable for large n (>100) due to cubic time

// 6) Recurrence Relation:
// M(i, j) = min{ M(i,k) + M(k,j) + arr[i]*arr[k]*arr[j] }, for i < k < j
// Base case: M(i,i) = 0

// 7) Summary (2 lines):
// Solves matrix chain multiplication problem using dynamic programming.
// Bottom-up and top-down methods are both polynomial but memory intensive.