#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define MAX_KEYS 100

// Function to print root table
void printRootTable(int root[MAX_KEYS][MAX_KEYS], int n) {
    printf("\nRoot Table:\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%4d", root[i][j]);
        }
        printf("\n");
    }
}

// Function to build OBST and return minimum expected cost
double optimalBST(int n, double p[], double q[], int root[][MAX_KEYS]) {
    double e[n + 2][n + 2]; // Expected cost table
    double w[n + 2][n + 2]; // Weight table

    // Initialize base cases
    for (int i = 1; i <= n + 1; i++) {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    // Fill tables bottom-up
    for (int l = 1; l <= n; l++) { // Length of subsequence
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            e[i][j] = DBL_MAX;
            w[i][j] = w[i][j - 1] + p[j] + q[j];

            // Try all possible roots in range
            for (int r = i; r <= j; r++) {
                double cost = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (cost < e[i][j]) {
                    e[i][j] = cost;
                    root[i][j] = r;
                }
            }
        }
    }

    // Minimum expected cost stored at e[1][n]
    return e[1][n];
}

// Function to recursively print root structure (optional)
void printTree(int rootTable[][MAX_KEYS], int i, int j, int parentSide, char* label) {
    if (i <= j) {
        int r = rootTable[i][j];
        int parent = parentSide;

        if (parent == 0)
            printf("%s is the root\n", label + r - 1);
        else if (parent > r)
            printf("%s is the right child of %s\n", label + r - 1, label + parent - 1);
        else
            printf("%s is the left child of %s\n", label + r - 1, label + parent - 1);

        printTree(rootTable, i, r - 1, r, label);   // Left subtree
        printTree(rootTable, r + 1, j, r, label);   // Right subtree
    }
}

// Driver program
int main() {
    int n;

    printf("Enter number of keys (max %d): ", MAX_KEYS);
    scanf("%d", &n);

    double p[n + 1], q[n + 1]; // 1-based indexing
    int rootTable[MAX_KEYS + 2][MAX_KEYS + 2];

    char labels[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // Labels for nodes

    printf("Enter success probabilities p[1..%d]:\n", n);
    for (int i = 1; i <= n; i++) {
        printf("p[%d] = ", i);
        scanf("%lf", &p[i]);
    }

    printf("Enter failure probabilities q[0..%d]:\n", n);
    for (int i = 0; i <= n; i++) {
        printf("q[%d] = ", i);
        scanf("%lf", &q[i]);
    }

    double minCost = optimalBST(n, p, q, rootTable);

    printf("\nMinimum expected search cost: %.4f\n", minCost);

    printf("\nRoot Table:\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%4d", rootTable[i][j]);
        }
        printf("\n");
    }

    printf("\nBinary Search Tree Structure:\n");
    printTree(rootTable, 1, n, 0, labels);

    return 0;
}




















// 1) Input:
// - n: Number of keys
// - p[1..n]: Success probabilities (probability that key i is accessed)
// - q[0..n]: Failure probabilities (probability of searching between keys)

// 2) Algorithm:
// Dynamic Programming approach:
// - Build expected cost table e[i][j] and weight table w[i][j]
// - For each subsequence length l from 1 to n
// - Try all possible roots r in [i, j] and choose minimum cost

// 3) Time Complexity:
// Best/Avg/Worst Case: O(n^3)
// Triple nested loops — outer loop over lengths, inner loops over ranges and root choices

// 4) Space Complexity:
// - O(n^2), due to two 2D DP tables (e[][] and w[][]) and root table

// 5) Advantages / Disadvantages:
// + Builds a tree with minimal expected search cost
// + Efficient for moderate-sized input sets
// - Cubic time complexity limits use for large n
// - Requires careful probability input handling

// 6) Recurrence Relation:
// e[i][j] = min{ e[i][r-1] + e[r+1][j] } + w[i][j], for r in [i, j]
// w[i][j] = w[i][j-1] + p[j] + q[j]

// 7) Summary (2 lines):
// Constructs optimal binary search tree using dynamic programming.
// Minimizes expected search cost for known access probabilities.