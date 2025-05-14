// 8) Dijkstra's Algorithm for Single-Source Shortest Path with Full Input and Path Display
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>

#define V 100

int minDistance(int dist[], bool sptSet[], int n) {
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < n; v++) {
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void printPath(int parent[], int j) {
    if (parent[j] == -1) {
        printf("%d", j);
        return;
    }
    printPath(parent, parent[j]);
    printf(" -> %d", j);
}

void printSolution(int dist[], int parent[], int n, int src) {
    printf("\nVertex\tDistance from Source\tPath\n");
    for (int i = 0; i < n; i++) {
        printf("%d -> %d\t%d\t\t", src, i, dist[i]);
        printPath(parent, i);
        printf("\n");
    }
}

void dijkstra(int graph[V][V], int src, int n) {
    int dist[V], parent[V];
    bool sptSet[V];

    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
        parent[i] = -1;
    }
    dist[src] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = minDistance(dist, sptSet, n);
        sptSet[u] = true;

        for (int v = 0; v < n; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    printSolution(dist, parent, n, src);
}

int main() {
    int n, e;
    int graph[V][V] = {0};

    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &e);

    printf("Enter edges in the format: source destination weight\n");
    for (int i = 0; i < e; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
        graph[v][u] = w; // Uncomment for undirected graph
    }

    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", graph[i][j]);
        }
        printf("\n");
    }

    int src;
    printf("Enter source vertex (0 to %d): ", n - 1);
    scanf("%d", &src);

    clock_t start = clock();
    dijkstra(graph, src, n);
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nTime taken: %f seconds\n", time_taken);

    return 0;
}
