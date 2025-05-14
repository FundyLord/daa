#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#include<limits.h>
#include<unistd.h>
#include<stdbool.h>
#define MAX 100
int V;

bool dfs(int s,int t,int *parent,int **residual,bool *visited)
{
    visited[s] = true;
    if(s==t) return true;

    for (int v = 0; v < V; v++)
    {
        if(!visited[v] & residual[s][v]>0)
        {
            parent[v] =s;
            if(dfs(v,t,parent,residual,visited)) return true;
        }
    }
    return false;
    
}

int fordFulkerson(int graph[][MAX],int s,int t)
{
    int ** residual = (int**)malloc(sizeof(int)*V);
    for (int i = 0; i < V; i++)
    {
        residual[i] = (int*)malloc(sizeof(int)*V);
    }
    memcpy(residual,graph,sizeof(int)*V);


    
    int maxFlow = 0;
   
    

    while(1)
    {
        bool *visited = (bool*)malloc(sizeof(bool)*V);
        memset(visited,false,sizeof(bool)*V);

        int *parent = (int*)malloc(sizeof(int)*V);
        memset(parent,-1,sizeof(int)*V);

        if(!dfs(s,t,parent,residual,visited)) break;

        int path_flow = INT_MAX;
        for (int v = t; v!=s; v=parent[v])
        {
            int u = parent[v];
            if(residual[u][v] < path_flow)
            {
                path_flow = residual[u][v];
            }
        }
        
        for (int v = t; v!=s; v=parent[v])
        {
            int u = parent[v];
            residual[u][v] -= path_flow;
            residual[v][u] += path_flow;

        }

        maxFlow+=path_flow;


    }

    return maxFlow;
   

}


int main()
{
    int graph[MAX][MAX] = {
        {0, 16, 13,  0,  0,  0},
        {0,  0, 10, 12,  0,  0},
        {0,  4,  0,  0, 14,  0},
        {0,  0,  9,  0,  0, 20},
        {0,  0,  0,  7,  0,  4},
        {0,  0,  0,  0,  0,  0}
    };
    
    int s = 0;
    int t = 5;
    V = 6;
    int maxFlow = fordFulkerson(graph,0,5);
    printf("Maximum flow from %d to %d is %d\n",s,t,maxFlow);
    return 0;
}
