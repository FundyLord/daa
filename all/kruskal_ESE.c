#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <stdbool.h>
#define MAX 100

typedef struct node Node;

typedef struct edge
{
    int src, dest, weight;
} Edge;

typedef struct
{
    int *parent;
    int *rank;
} DSUF;

typedef struct graph
{
    int V;
    int E;
    Edge *edges;
} Graph;

Graph *createGraph(int V, int E)
{
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->V = V;
    g->E = E;

    g->edges = (Edge *)malloc(sizeof(Edge) * E);

    return g;
}
DSUF *init(int V)
{
    DSUF *dsuf = (DSUF *)malloc(sizeof(DSUF));
    dsuf->parent = (int *)malloc(sizeof(int) * V);
    dsuf->rank = (int *)malloc(sizeof(int) * V);
    memset(dsuf->rank, 0, sizeof(int) * V);
    for (int i = 0; i < V; i++)
        dsuf->parent[i] = i;
    return dsuf;
}

int find(DSUF *dsuf, int v)
{
    if (dsuf->parent[v] != v)
        return dsuf->parent[v] = find(dsuf, dsuf->parent[v]);
    return dsuf->parent[v];
}

int unionSets(DSUF *dsuf, int x, int y)
{
    int rootX = find(dsuf, x);
    int rootY = find(dsuf, y);
    int rankX = dsuf->rank[rootX];
    int rankY = dsuf->rank[rootY];

    if (rootX != rootY)
    {
        if (rankX > rankY)
        {
            dsuf->parent[rootY] = rootX;
        }
        else if (rankX < rankY)
        {
            dsuf->parent[rootX] = rootY;
        }
        else
        {
            dsuf->parent[rootY] = rootX;
            dsuf->rank[rootX]++;
        }
    }
}
int compareEdges(const void *a, const void *b)
{
    return ((Edge *)a)->weight - ((Edge *)b)->weight;
}

void kruskal(Graph *g)
{
    qsort(g->edges, g->E, sizeof(Edge), compareEdges);

    DSUF *dsuf = init(g->V);
    Edge result[g->V-1];
    int e = 0;
    int MSTweight = 0;
    int i = 0;
    while (e < g->V - 1 && i < g->E)
    {
        int src = g->edges[i].src;
        int dest = g->edges[i].dest;

        int parSRC = find(dsuf, src);
        int parDEST = find(dsuf, dest);

        if (parSRC != parDEST)
        {
            unionSets(dsuf, parSRC, parDEST);
            result[e++] = g->edges[i];
            MSTweight += g->edges[i].weight;
        }

        i++;
    }

    printf("MST weight : %d\n",MSTweight);
    for (int i = 0; i < g->V-1; i++)
    {
        printf("%d %d  w = %d\n",result[i].src,result[i].dest,result[i].weight);
    }
    
}
int main(int argc, char const *argv[])
{
    int V, E;
    int src, dest, weight;
    Graph *g;

    printf("Vertices : ");
    scanf("%d", &V);

    printf("Edges : ");
    scanf("%d", &E);

    g = createGraph(V,E);

    printf("Enter edges (s d w) format : \n");
    for (int i = 0; i < E; i++)
    {
        scanf("%d %d %d", &src, &dest, &weight);
        g->edges[i].src = src;
        g->edges[i].dest = dest;
        g->edges[i].weight = weight;
    }

    kruskal(g);

    return 0;
}
