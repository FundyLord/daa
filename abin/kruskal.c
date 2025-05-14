// 14) Minimum Spanning Tree (MST) Algorithm: Kruskal’s Algorithm
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure for an edge
struct Edge {
    int src, dest, weight;
};

// Structure for the subset for Union-Find
struct Subset {
    int parent;
    int rank;
};

// Function to find the subset of an element (with path compression)
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

// Function to do Union of two subsets (by rank)
void Union(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank) {
        subsets[xroot].parent = yroot;
    } else if (subsets[xroot].rank > subsets[yroot].rank) {
        subsets[yroot].parent = xroot;
    } else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Function to compare two edges (for sorting by weight)
int compare(const void *a, const void *b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

// Kruskal's Algorithm to find the MST
void kruskal(struct Edge edges[], int V, int E) {
    struct Edge result[V];  // Array to store the resultant MST
    int e = 0;  // Count of edges in MST
    int i = 0;  // Initial index of sorted edges
    struct Subset *subsets = (struct Subset*) malloc(V * sizeof(struct Subset));

    // Initialize subsets for Union-Find
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Sort edges in increasing order of weights
    qsort(edges, E, sizeof(edges[0]), compare);

    // Loop through sorted edges and construct MST
    while (e < V - 1 && i < E) {
        struct Edge next_edge = edges[i++];
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // If including this edge does not cause a cycle
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    // Print the MST
    printf("Following are the edges in the MST:\n");
    int mstWeight = 0;
    for (int i = 0; i < e; i++) {
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
        mstWeight += result[i].weight;
    }

    printf("Weight of the MST: %d\n", mstWeight);

    free(subsets);
}

int main() {
    int V, E;

    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    printf("Enter the number of edges: ");
    scanf("%d", &E);

    struct Edge *edges = (struct Edge*) malloc(E * sizeof(struct Edge));

    printf("Enter the edges (src dest weight):\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);
    }

    clock_t start = clock();
    kruskal(edges, V, E);
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nTime taken: %f seconds\n", time_taken);

    free(edges);
    return 0;
}
