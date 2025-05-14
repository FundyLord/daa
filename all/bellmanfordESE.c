#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <stdbool.h>
#define MAX 100
typedef struct edge
{
    int s, d, w;
} Edge;

bool bellmanFord(Edge *edges, int src, int V, int E, int *dist)
{
    int i, j, k;
    for (i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
    }
    dist[src] = 0;

    for (int i = 0; i < V - 1; i++)
    {
        for (j = 0; j < E; j++)
        {

            int w = edges[j].w;
            int u = edges[j].s;
            int v = edges[j].d;

            if (dist[u] != INT_MAX && dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
            }
        }

        
    }

    for (j = 0; j < E; j++)
        {

            int w = edges[j].w;
            int u = edges[j].s;
            int v = edges[j].d;

            if (dist[u] != INT_MAX && dist[u] + w < dist[v])

            {
                return false;
            }
        }

    return true;
}
int main() {
    int V = 9, E = 29;
    Edge edges[] = {
        {0, 1, 4}, {0, 7, 8},
        {1, 0, 4}, {1, 2, 8}, {1, 7, 11},
        {2, 1, 8}, {2, 3, 7}, {2, 5, 4}, {2, 8, 2},
        {3, 2, 7}, {3, 4, 9}, {3, 5, 14},
        {4, 3, 9}, {4, 5, 10},
        {5, 2, 4}, {5, 3, 14}, {5, 4, 10}, {5, 6, 2},
        {6, 5, 2}, {6, 7, 1}, {6, 8, 6},
        {7, 0, 8}, {7, 1, 11}, {7, 6, 1}, {7, 8, 7},
        {8, 2, 2}, {8, 6, 6}, {8, 7, 7}
    };
    

    int dist[MAX];
    if (bellmanFord(edges, 0, V, E, dist)) {
        printf("Vertex Distance from Source:\n");
        for (int i = 0; i < V; i++)
            printf("%d \t %d\n", i, dist[i]);
    } else {
        printf("Graph contains a negative weight cycle\n");
    }

    return 0;
}

