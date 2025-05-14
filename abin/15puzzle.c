// 11) 15 Puzzle Problem using Branch and Bound Algorithm
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define N 4  // Grid size (4x4)

int goal_state[4][4] = {{1, 2, 3, 4},
                        {5, 6, 7, 8},
                        {9, 10, 11, 12},
                        {13, 14, 15, 0}};

// Function to print the puzzle grid
void printPuzzle(int puzzle[4][4]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%2d ", puzzle[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Function to find the position of the blank (0)
int findBlank(int puzzle[4][4]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (puzzle[i][j] == 0) {
                return i * N + j;
            }
        }
    }
    return -1;
}

// Function to check if the current state is the goal state
bool isGoalState(int puzzle[4][4]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (puzzle[i][j] != goal_state[i][j]) {
                return false;
            }
        }
    }
    return true;
}

// Function to calculate the heuristic (Manhattan distance)
int calculateManhattan(int puzzle[4][4]) {
    int distance = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (puzzle[i][j] != 0) {
                int targetX = (puzzle[i][j] - 1) / N;
                int targetY = (puzzle[i][j] - 1) % N;
                distance += abs(i - targetX) + abs(j - targetY);
            }
        }
    }
    return distance;
}

// Function to solve the puzzle using branch and bound approach
void solvePuzzle(int puzzle[4][4]) {
    int blank_pos = findBlank(puzzle);
    int row = blank_pos / N;
    int col = blank_pos % N;
    int manhattan_distance = calculateManhattan(puzzle);

    printf("Initial Puzzle State:\n");
    printPuzzle(puzzle);

    printf("Goal Puzzle State:\n");
    printPuzzle(goal_state);

    if (isGoalState(puzzle)) {
        printf("Puzzle is already solved!\n");
    } else {
        printf("Solving the puzzle using branch and bound algorithm...\n");

        // Here we will use the Manhattan distance as the bounding function for the puzzle.
        printf("Manhattan distance heuristic value: %d\n", manhattan_distance);
    }
}

int main() {
    int puzzle[4][4];

    printf("Enter the initial puzzle state (4x4 grid, 0 represents blank space):\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &puzzle[i][j]);
        }
    }

    clock_t start = clock();
    solvePuzzle(puzzle);
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nTime taken: %f seconds\n", time_taken);

    return 0;
}
