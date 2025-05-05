#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
//Edmonds-Karp Algorithm bhi h - BFS version of fordfulkerson
#define V 20  // Number of vertices in the graph

// Queue for BFS
typedef struct {
    int* items;
    int front;
    int rear;
} Queue;

Queue* createQueue(int size) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->items = (int*)malloc(size * sizeof(int));
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

void enqueue(Queue* queue, int item) {
    if (queue->front == -1) queue->front = 0;
    queue->rear++;
    queue->items[queue->rear] = item;
}

int dequeue(Queue* queue) {
    if (queue->front == -1 || queue->front > queue->rear) {
        return -1; // Empty
    }
    int val = queue->items[queue->front];
    queue->front++;
    return val;
}

bool isEmpty(Queue* queue) {
    return queue->front == -1 || queue->front > queue->rear;
}

// Function to perform BFS and find path from source to sink
bool bfs(int rGraph[V][V], int s, int t, int parent[]) {
    bool visited[V];
    memset(visited, 0, sizeof(visited));

    Queue* q = createQueue(V);
    enqueue(q, s);
    visited[s] = true;
    parent[s] = -1;

    while (!isEmpty(q)) {
        int u = dequeue(q);

        for (int v = 0; v < V; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                parent[v] = u;
                if (v == t) {
                    free(q->items);
                    free(q);
                    return true;
                }
                visited[v] = true;
                enqueue(q, v);
            }
        }
    }

    free(q->items);
    free(q);
    return false;
}

// Returns maximum flow from s to t in a graph
int fordFulkerson(int graph[V][V], int s, int t) {
    int u, v;

    // Create a residual graph and fill it with original capacities
    int rGraph[V][V];
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
            rGraph[u][v] = graph[u][v];

    int parent[V]; // To store path
    int max_flow = 0;

    // Augment the flow while there is a path from source to sink
    while (bfs(rGraph, s, t, parent)) {
        // Find minimum residual capacity on the found path
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            if (rGraph[u][v] < path_flow)
                path_flow = rGraph[u][v];
        }

        // Update residual capacities along the path
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        // Add path flow to overall flow
        max_flow += path_flow;
    }

    return max_flow;
}

// Driver program
int main() {
    // Sample graph as adjacency matrix (capacity only)
    int graph[V][V];

    // Initialize all capacities to zero
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            graph[i][j] = 0;

    // Manually define a sample graph with 6 nodes (0 to 5), rest are zero
    graph[0][1] = 16;
    graph[0][2] = 13;
    graph[1][2] = 10;
    graph[1][3] = 12;
    graph[2][1] = 4;
    graph[2][4] = 14;
    graph[3][2] = 9;
    graph[3][5] = 20;
    graph[4][3] = 7;
    graph[4][5] = 4;

    // Run Ford-Fulkerson
    int source = 0, sink = 5;
    int maxFlow = fordFulkerson((int (*)[V])graph, source, sink);

    printf("Maximum flow from Source (%d) to Sink (%d): %d\n", source, sink, maxFlow);

    return 0;
}



//ford-fulkerson using dfs 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define V 20  // Max number of vertices

// Residual graph represented as adjacency matrix
int rGraph[V][V];

// Function to perform DFS and find path from source to sink
bool dfs(int u, int t, int parent[], bool visited[]) {
    visited[u] = true;

    if (u == t)
        return true;

    for (int v = 0; v < V; v++) {
        if (!visited[v] && rGraph[u][v] > 0) {
            parent[v] = u;
            if (dfs(v, t, parent, visited))
                return true;
        }
    }

    return false;
}

// Returns maximum flow from s to t in a graph using DFS
int fordFulkersonDFS(int graph[V][V], int s, int t) {
    // Create a residual graph and fill it with original capacities
    memcpy(rGraph, graph, sizeof(rGraph));

    int parent[V]; // To store path
    int max_flow = 0;

    bool visited[V];

    // Augment the flow while there is a path from source to sink
    while (1) {
        memset(visited, 0, sizeof(visited));
        if (!dfs(s, t, parent, visited))
            break;

        // Find minimum residual capacity on the found path
        int path_flow = INT_MAX;
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            if (rGraph[u][v] < path_flow)
                path_flow = rGraph[u][v];
        }

        // Update residual capacities along the path
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        // Add path flow to overall flow
        max_flow += path_flow;
    }

    return max_flow;
}

// Driver program
int main() {
    // Sample graph as adjacency matrix (capacity only)
    int graph[V][V];

    // Initialize all capacities to zero
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            graph[i][j] = 0;

    // Manually define a sample graph with 6 nodes (0 to 5), rest are zero
    graph[0][1] = 16;
    graph[0][2] = 13;
    graph[1][2] = 10;
    graph[1][3] = 12;
    graph[2][1] = 4;
    graph[2][4] = 14;
    graph[3][2] = 9;
    graph[3][5] = 20;
    graph[4][3] = 7;
    graph[4][5] = 4;

    // Run Ford-Fulkerson using DFS
    int source = 0, sink = 5;
    int maxFlow = fordFulkersonDFS((int (*)[V])graph, source, sink);

    printf("Maximum flow from Source (%d) to Sink (%d): %d\n", source, sink, maxFlow);

    return 0;
}























// 1) Input:
// - Directed graph represented as V x V adjacency matrix
//   - graph[i][j] = capacity from node i to j
// - Source and sink nodes (s, t)
// - BFS version uses queue; DFS version uses recursion

// 2) Algorithm:
// Ford-Fulkerson Method:
// - Repeatedly find augmenting paths in residual graph
// - Update flow and residual capacities
// BFS variant: Edmonds-Karp algorithm (uses shortest path in terms of edges)
// DFS variant: Basic DFS-based flow augmentation

// 3) Time Complexity:
// BFS Version (Edmonds-Karp): O(V * E^2)
// DFS Version: O(E * F), where F = max flow (can be slow with poor path choices)

// 4) Space Complexity:
// - O(V + E), for residual graph and parent/visited arrays

// 5) Advantages / Disadvantages:
// BFS (Edmonds-Karp):
// + Faster convergence due to shortest path selection
// + Polynomial time bound
// DFS:
// + Simpler and easier to implement
// - Can be very slow or get stuck in worst-case paths

// 6) Recurrence Relation:
// Not applicable directly — flow updated iteratively per augmenting path

// 7) Summary (2 lines):
// Implements Ford-Fulkerson max-flow algorithm using both BFS (Edmonds-Karp) and DFS.
// BFS is preferred for performance; DFS is simpler but less predictable.