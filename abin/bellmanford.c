#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>

#define V 100

// Function to print the path from source to current vertex
void printPath(int parent[], int j) {
    if (parent[j] == -1) {
        printf("%d", j);
        return;
    }
    printPath(parent, parent[j]);
    printf(" -> %d", j);
}

// Function to print the final result: shortest distances and paths
void printSolution(int dist[], int parent[], int n, int src) {
    printf("\nVertex\tDistance from Source\tPath\n");
    for (int i = 0; i < n; i++) {
        printf("%d -> %d\t%d\t\t", src, i, dist[i]);
        printPath(parent, i);
        printf("\n");
    }
}

// Function to print negative cycle if found
void printNegativeCycle(int parent[], int n, int cycleStart) {
    int cycle[V];
    for (int i = 0; i < n; i++) cycle[i] = -1;

    // Find the cycle
    for (int i = 0; i < n; i++) {
        if (parent[i] != -1 && cycle[i] == -1) {
            cycleStart = i;
            break;
        }
    }

    if (cycleStart != -1) {
        printf("\nNegative Cycle Detected: ");
        int current = cycleStart;
        do {
            printf("%d -> ", current);
            current = parent[current];
        } while (current != cycleStart);
        printf("%d\n", cycleStart);
    }
}

// Bellman-Ford algorithm to find shortest path and detect negative cycles
void bellmanFord(int graph[V][3], int src, int n, int e) {
    int dist[V], parent[V];

    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        parent[i] = -1;
    }
    dist[src] = 0;

    // Relax all edges (n-1) times
    for (int i = 1; i < n; i++) { // Relax all edges for n-1 times
        for (int j = 0; j < e; j++) {
            int u = graph[j][0], v = graph[j][1], w = graph[j][2];
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
            }
        }
    }

    // Check for negative weight cycles by performing one more relaxation
    for (int i = 0; i < e; i++) {
        int u = graph[i][0], v = graph[i][1], w = graph[i][2];
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            printf("\nNegative weight cycle detected!\n");
            printNegativeCycle(parent, n, v);
            return;
        }
    }

    printSolution(dist, parent, n, src);
}

int main() {
    int n, e;
    int graph[V][3]; // Store edges as (src, dest, weight)

    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &e);

    printf("Enter edges in the format: source destination weight\n");
    for (int i = 0; i < e; i++) {
        scanf("%d %d %d", &graph[i][0], &graph[i][1], &graph[i][2]);
    }

    int src;
    printf("Enter source vertex (0 to %d): ", n - 1);
    scanf("%d", &src);

    clock_t start = clock();
    bellmanFord(graph, src, n, e); // Call Bellman-Ford with edge list
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nTime taken: %f seconds\n", time_taken);

    return 0;
}
