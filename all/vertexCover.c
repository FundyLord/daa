#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#define MAX 100

int graph[MAX][MAX];
int V;
int E;

void approxVertexCover()
{
    bool selected[MAX] = {false};
    bool visited[MAX] = {false};

    // while(1)
    // {
    //     int maxDeg = 0;
    //     int vertex = -1;

    //     for (int i = 0; i < V; i++)
    //     {
    //         if(visited[i]) continue;

    //         int deg = 0;
    //         for (int j = 0; j < V; j++)
    //         {
    //             if(graph[i][j] && !visited[j]) 
    //                 deg++;
    //         }

    //         if(deg > maxDeg)
    //         {
    //             maxDeg = deg;
    //             vertex = i;
    //         }
        
    //     }

    //     printf("MAX VERTEX = %d\n",vertex);

    //     if(vertex==-1)
    //         break;

    //     for (int j = 0; j < V; j++)
    //     {
    //         if(graph[vertex][j] && !visited[j])
    //         {
    //             visited[vertex] = visited[j] = selected[j] = selected[vertex] = true;
    //             break;
    //         }
    //     }
        
        
    // }

    for (int u = 0; u < V; u++)
    {
        if(visited[u]) continue;
        for (int v = 0; v < V; v++)
        {
            if(graph[u][v] && !visited[v])
            {
                selected[u] =  selected[v] = true;
                visited[u]=visited[v]=true;
                break;
            }
        }
        
    }
    

    printf("Vertex Cover : \n");
    for (int i = 0; i < V; i++)
    {
        if(selected[i])
        {
            printf("Vertex %d\n",i);
        }
    }
    
    
}
int main()
{
    int src,dest;

    printf("Enter num vertices : ");
    scanf("%d", &V);

    printf("Enter num edges : ");
    scanf("%d",&E);

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            graph[i][j]=0;
        }
    }
    
    for (int i = 0; i < E; i++)
    {
        printf("Enter edge %d (u v) : ",i+1);
        scanf("%d %d", &src,&dest);

        graph[src][dest] = graph[dest][src] = 1;

    }
    

    approxVertexCover();
    return 0;
}
