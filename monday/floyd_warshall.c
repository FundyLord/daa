#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 4       // Number of vertices
#define INF 99999  // Representing infinity

// Function to print the solution matrix
void printSolution(int dist[][V]) {
    printf("Shortest Distance Matrix:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                printf("INF\t");
            else
                printf("%d\t", dist[i][j]);
        }
        printf("\n");
    }
}

// Function to run Floyd-Warshall Algorithm
void floydWarshall(int graph[][V]) {
    int dist[V][V];

    // Step 1: Initialize distance matrix same as input graph
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            dist[i][j] = graph[i][j];

    // Step 2: Update distances using every vertex as intermediate node
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                // If vertex k improves shortest path from i to j
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Step 3: Check for negative-weight cycles
    for (int i = 0; i < V; i++) {
        if (dist[i][i] < 0) {
            printf("Graph contains a negative-weight cycle.\n");
            return;
        }
    }

    // Print final shortest paths
    printSolution(dist);
}

// Driver program
int main() {
    /* Example Graph with 4 nodes
       INF = No Edge
       Negative edge weights allowed but no negative cycles
    */
    int graph[V][V] = {
        {0, 3, INF, 5},
        {2, 0, INF, 4},
        {INF, 1, 0, INF},
        {1, INF, 2, 0}
    };

    printf("Running Floyd-Warshall Algorithm...\n");
    floydWarshall(graph);

    return 0;
}
















// 1) Input:
// - V x V adjacency matrix (graph[V][V])
//   - graph[i][j] = weight of edge from i to j
//   - Use INF to represent no direct edge
//   - Self loops allowed, negative edges allowed but no negative cycles

// 2) Algorithm:
// - Dynamic Programming approach
// - Consider every vertex as intermediate node
// - Update dist[i][j] if path i -> k -> j is shorter
// - Detects negative-weight cycles via diagonal entries

// 3) Time Complexity:
// Best/Avg/Worst Case: O(V^3)
// Triple nested loops over all vertices

// 4) Space Complexity:
// - O(V^2), for distance matrix (dist[V][V])

// 5) Advantages / Disadvantages:
// + Handles negative edge weights
// + Finds shortest paths between all pairs
// - Fails with negative cycles (must be detected separately)
// - High cubic time complexity not suitable for large graphs

// 6) Recurrence Relation:
// dist[k][i][j] = min(dist[k-1][i][j], dist[k-1][i][k] + dist[k-1][k][j])
// Implemented in-place using a single 2D array

// 7) Summary (2 lines):
// Solves all-pairs shortest path problem using dynamic programming.
// Efficient for small graphs but not scalable due to O(V^3) time.