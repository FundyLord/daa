#include <stdio.h>
#include <stdbool.h>

#define V 4   // Number of vertices
#define MAX_COLORS 3  // Maximum number of colors allowed

// Utility function to check if color can be assigned to vertex v
bool isSafe(int v, bool graph[V][V], int color[], int c) {
    for (int i = 0; i < V; i++)
        if (graph[v][i] && c == color[i])
            return false;
    return true;
}

// Recursive backtracking function
bool graphColoringUtil(bool graph[V][V], int m, int color[], int v) {
    // Base case: If all vertices are assigned a color
    if (v == V)
        return true;

    // Try different colors for current vertex
    for (int c = 1; c <= m; c++) {
        // Check if assignment is safe
        if (isSafe(v, graph, color, c)) {
            color[v] = c;

            // Recur to assign colors to remaining vertices
            if (graphColoringUtil(graph, m, color, v + 1))
                return true;

            // If assigning color c doesn't lead to solution, backtrack
            color[v] = 0;
        }
    }

    // If no color can be assigned to this vertex
    return false;
}

// Main function to solve graph coloring problem
void graphColoring(bool graph[V][V], int m) {
    int color[V];  // Stores color assigned to each vertex
    for (int i = 0; i < V; i++)
        color[i] = 0;

    // Call recursive utility
    if (!graphColoringUtil(graph, m, color, 0)) {
        printf("Solution does not exist\n");
        return;
    }

    // Print solution
    printf("Solution exists:\n");
    printf("Vertex   Color\n");
    for (int i = 0; i < V; i++)
        printf(" %d        %d\n", i, color[i]);
}

// Driver program
int main() {
    /* Create the following graph
       (0)---(1)
        |     |
       (2)---(3)
    */
    bool graph[V][V] = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0}
    };

    int m = 3;  // Number of available colors

    printf("Solving Graph Coloring Problem...\n");
    graphColoring(graph, m);

    return 0;
}















// 1) Input:
// - Adjacency matrix graph[V][V] representing undirected graph
// - m: maximum number of colors allowed

// 2) Algorithm:
// Backtracking approach:
// - Assign color to one vertex at a time
// - Only assign valid colors (no adjacent same color)
// - If no valid color, backtrack and try different previous assignment

// 3) Time Complexity:
// Best Case: O(V), if solution found immediately
// Worst Case: O(m^V), all possible color combinations explored

// 4) Space Complexity:
// - O(V), for color array and recursion stack depth

// 5) Advantages / Disadvantages:
// + Simple and intuitive for small graphs
// + Works well when m is large relative to degree
// - Inefficient for large graphs or high chromatic numbers
// - Exponential in worst case

// 6) Recurrence Relation:
// T(V) = m * T(V-1), leading to T(V) = O(m^V)

// 7) Summary (2 lines):
// Solves graph coloring problem using recursive backtracking.
// Guaranteed correct but exponential in worst-case scenario.