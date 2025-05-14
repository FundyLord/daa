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


void prims(Graph *g)
{
    int * key = (int*)malloc(sizeof(int)*g->V);
    int * parent = (int*)malloc(sizeof(int)*g->V);
    bool * inMST = (bool*)malloc(sizeof(bool)*g->V);

    for (int i = 0; i < g->V; i++) {
        key[i] = INT_MAX;
        inMST[i] = false;
    }
    
    key[0] = 0;
    parent[0] = -1;
    int totalWeight = 0;
    int minVertex,minKey;
    for (int count = 0; count < g->V-1; count++)
    {
        minVertex = -1;
        minKey = INT_MAX;
        for (int v = 0; v < g->V; v++)
        {
            if(!inMST[v] && key[v]<minKey)
            {
                minKey = key[v];
                minVertex = v;
            }
        }

        inMST[minVertex] = true;
        totalWeight += minKey;

        for (int i = 0; i < g->E; i++)
        {
            Edge edge = g->edges[i];
            int u = edge.src;
            int v = edge.dest;

            if(u==minVertex && !inMST[v] && edge.weight < key[v])
            {
                key[v] = edge.weight;
                parent[v] = u;
            }
            else if(v==minVertex && !inMST[u] && edge.weight < key[u])
            {
                key[u] = edge.weight;
                parent[u] = v;
            }
        }        
    }
    printf("MST Weight : %d",totalWeight);
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

    prims(g);

    return 0;
}
