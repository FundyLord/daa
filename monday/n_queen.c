#include <stdio.h>
#include <stdbool.h>

#define MAX_N 20  // Maximum board size

// Global variables
int board[MAX_N][MAX_N];  // Chess board
int solutions = 0;        // Count of solutions

// Function to print board
void printBoard(int n) {
    printf("Solution #%d:\n", solutions + 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%s ", board[i][j] ? "Q" : ".");
        }
        printf("\n");
    }
    printf("\n");
}

// Utility function to check if queen can be placed at (row, col)
bool isSafe(int board[MAX_N][MAX_N], int row, int col, int n) {
    int i, j;

    // Check this row on left side
    for (i = 0; i < col; i++)
        if (board[row][i])
            return false;

    // Check upper diagonal on left side
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    // Check lower diagonal on left side
    for (i = row, j = col; i < n && j >= 0; i++, j--)
        if (board[i][j])
            return false;

    return true;
}

// Recursive function to solve N Queens using backtracking
bool solveNQueensUtil(int board[MAX_N][MAX_N], int col, int n) {
    // Base case: If all queens are placed
    if (col == n) {
        solutions++;
        printBoard(n);
        return false; // To find all solutions
    }

    bool res = false;
    for (int i = 0; i < n; i++) {
        if (isSafe(board, i, col, n)) {
            // Place this queen
            board[i][col] = 1;

            // Recur to place rest of the queens
            res = solveNQueensUtil(board, col + 1, n) || res;

            // Backtrack
            board[i][col] = 0;  // Remove queen
        }
    }

    return res;
}

// Main function to solve N-Queens problem
void solveNQueens(int n) {
    // Initialize board with zeros
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            board[i][j] = 0;

    solutions = 0;

    if (!solveNQueensUtil(board, 0, n))
        printf("No solution exists for %d-Queens\n", n);
    else
        printf("Total Solutions Found: %d\n", solutions);
}

// Driver program
int main() {
    int n;

    printf("Enter number of queens (N): ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_N) {
        printf("Invalid input. N must be between 1 and %d\n", MAX_N);
        return 1;
    }

    solveNQueens(n);

    return 0;
}














// 1) Input:
// - Integer n: number of queens and size of board (n x n)
// - Queens must be placed such that no two attack each other

// 2) Algorithm:
// Recursive backtracking:
// - Try placing a queen in each column from left to right
// - Check safety using row, upper/lower diagonals
// - If safe, place queen and recurse for next column
// - Backtrack if no valid placement found

// 3) Time Complexity:
// Best Case: O(n!), worst-case exponential growth
// Each level has decreasing choices per queen (n, n−1, ..., 1)

// 4) Space Complexity:
// - O(n^2), for n x n chess board
// - O(n), recursion stack depth (max n levels)

// 5) Advantages / Disadvantages:
// + Simple and intuitive recursive approach
// + Finds all possible solutions
// - Inefficient for large n due to factorial time complexity
// - High memory usage for board storage

// 6) Recurrence Relation:
// T(n) = n * T(n - 1) + O(n), where O(n) is safety check
// Solves to T(n) ≈ O(n!) — much slower than polynomial algorithms

// 7) Summary (2 lines):
// Solves N-Queens problem using recursive backtracking with pruning.
// Finds all valid placements but becomes slow for N > 10–12.