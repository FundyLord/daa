#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <stdbool.h>
#define MAX 100

typedef struct vert
{
    int number;
    int dist;
} Vertex;

void swap(Vertex *x, Vertex *y)
{
    Vertex t = *x;
    *x = *y;
    *y = t;
}


int heapify(Vertex *vertices, int n, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && vertices[left].dist < vertices[smallest].dist)
    {
        smallest = left;
    }
    if (right < n && vertices[right].dist < vertices[smallest].dist)
    {
        smallest = right;
    }

    if (smallest != i)
    {
        swap(&vertices[smallest], &vertices[i]);
        heapify(vertices, n, smallest);
    }
}

int buildMinHeap(Vertex *v, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(v, n, i);
    }
}

Vertex extractMin(Vertex *vertices, int *n)
{
    Vertex root = vertices[0];
    vertices[0] = vertices[*n - 1];
    (*n)--;
    heapify(vertices, *n, 0);
    return root;
}



int relaxEdge(int u, int v, int w, Vertex *vertices)
{
    if(vertices[u].dist + w < vertices[v].dist)
    {
        vertices[v].dist = w + vertices[u].dist;
        return 1;
    }
    return 0;
}
void dijkstra(int graph[][MAX], int src, int V)
{
    Vertex *vertices = (Vertex *)malloc(sizeof(Vertex) * V);
    Vertex *heap = (Vertex *)malloc(sizeof(Vertex) * V);
    bool *inHeap = (bool*)malloc(sizeof(bool)*V);
    memset(inHeap,true,sizeof(bool)*V);

    // sssp init
    for (int i = 0; i < V; i++)
    {
        vertices[i].number = i;
        vertices[i].dist = INT_MAX;
    }
    vertices[src].dist = 0;

    for (int i = 0; i < V; i++)
    {
        heap[i] = vertices[i];
    }

    int heapSize = V;
    buildMinHeap(heap,heapSize);

    while(heapSize > 0)
    {
        Vertex u = extractMin(heap,&heapSize);
        inHeap[u.number] = false;

        for (int v = 0; v < V; v++)
        {
            if(graph[u.number][v]>0 && inHeap[v])
            {
                if(relaxEdge(u.number,v,graph[u.number][v],vertices))
                {
                    for (int i = 0; i < V; i++)
                    {
                        if(heap[i].number==v)
                        {
                            heap[i].dist = vertices[v].dist;
                            break;
                        }
                    }
                    
                    buildMinHeap(heap,heapSize);
                }
            }
        }
        
    }

    for (int i = 0; i < V; i++)
    {
        printf(" %d   %d\n",vertices[i].number,vertices[i].dist);
    }
    

    
}
int main() {
    int graph[MAX][MAX] = {
        {0, 4, 0, 0, 0, 0, 0, 8, 0},
        {4, 0, 8, 0, 0, 0, 0, 11, 0},
        {0, 8, 0, 7, 0, 4, 0, 0, 2},
        {0, 0, 7, 0, 9, 14, 0, 0, 0},
        {0, 0, 0, 9, 0, 10, 0, 0, 0},
        {0, 0, 4, 14, 10, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 1, 6},
        {8, 11, 0, 0, 0, 0, 1, 0, 7},
        {0, 0, 2, 0, 0, 0, 6, 7, 0}
    };
    int V = 9;
    int src = 0;

    dijkstra(graph, src, V);

    return 0;
}