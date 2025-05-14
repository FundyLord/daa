// 15) Minimum Spanning Tree (MST) Algorithm: Prim’s Algorithm
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define MAX 100

// Function to find the vertex with the minimum key value
int minKey(int key[], int mstSet[], int V) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++) {
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

// Function to implement Prim's Algorithm to find the MST
void primMST(int graph[MAX][MAX], int V) {
    int parent[MAX]; // Array to store the constructed MST
    int key[MAX]; // Key values used to pick the minimum weight edge
    int mstSet[MAX]; // To represent vertices included in MST

    // Initialize all keys as INFINITE and mstSet as false
    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }
    key[0] = 0; // Start with the first vertex
    parent[0] = -1; // The first vertex is the root of the MST

    // The MST will have V vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum key vertex from the set of vertices not yet processed
        int u = minKey(key, mstSet, V);
        mstSet[u] = 1; // Include the picked vertex in the MST

        // Update key values and parent indices of the adjacent vertices
        for (int v = 0; v < V; v++) {
            // graph[u][v] is non-zero only for adjacent vertices
            // mstSet[v] is false if v is not yet included in MST
            // Update the key value of v only if the new key is smaller than the current key
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    // Print the MST
    printf("Edge \tWeight\n");
    int mstWeight = 0;
    for (int i = 1; i < V; i++) {
        printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
        mstWeight += graph[i][parent[i]];
    }
    printf("Weight of the MST: %d\n", mstWeight);
}

int main() {
    int V, E;
    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    printf("Enter the number of edges: ");
    scanf("%d", &E);

    int graph[MAX][MAX];
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            graph[i][j] = 0; // Initialize the graph with 0 (no edge)
        }
    }

    printf("Enter the edges (src dest weight):\n");
    for (int i = 0; i < E; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
        graph[v][u] = w; // For undirected graph
    }

    clock_t start = clock();
    primMST(graph, V);
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nTime taken: %f seconds\n", time_taken);

    return 0;
}
