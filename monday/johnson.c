#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100

// Edge structure for Bellman-Ford
typedef struct {
    int u, v, weight;
} Edge;

// Graph representation using adjacency list
typedef struct {
    int V, E;
    Edge* edge;
} BellmanGraph;

// Node for Dijkstra's algorithm
typedef struct {
    int dest;
    int weight;
} AdjNode;

// Adjacency List
typedef struct {
    AdjNode* head;
    int size;
    int capacity;
} AdjList;

// Graph for Dijkstra
typedef struct {
    int V;
    AdjList* array;
} DijkstraGraph;

// Function to create a new Dijkstra graph
DijkstraGraph* createDijkstraGraph(int V) {
    DijkstraGraph* graph = (DijkstraGraph*)malloc(sizeof(DijkstraGraph));
    graph->V = V;
    graph->array = (AdjList*)malloc(V * sizeof(AdjList));
    for (int i = 0; i < V; ++i) {
        graph->array[i].head = NULL;
        graph->array[i].size = 0;
        graph->array[i].capacity = 0;
    }
    return graph;
}

// Add edge to Dijkstra graph
void addEdge(DijkstraGraph* graph, int src, int dest, int weight) {
    int cap = graph->array[src].capacity;
    if (graph->array[src].size == cap) {
        cap = cap ? cap * 2 : 1;
        graph->array[src].head = realloc(graph->array[src].head, cap * sizeof(AdjNode));
        graph->array[src].capacity = cap;
    }

    AdjNode node = {dest, weight};
    graph->array[src].head[graph->array[src].size++] = node;
}

// Create Bellman-Ford graph
BellmanGraph* createBellmanGraph(int V, int E) {
    BellmanGraph* graph = (BellmanGraph*)malloc(sizeof(BellmanGraph));
    graph->V = V;
    graph->E = E;
    graph->edge = (Edge*)malloc(E * sizeof(Edge));
    return graph;
}

// Bellman-Ford algorithm
int bellmanFord(BellmanGraph* graph, int source, int dist[]) {
    int V = graph->V;
    int E = graph->E;

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[source] = 0;

    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edge[j].u;
            int v = graph->edge[j].v;
            int w = graph->edge[j].weight;

            if (dist[u] != INT_MAX && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }

    // Check for negative-weight cycles
    for (int j = 0; j < E; j++) {
        int u = graph->edge[j].u;
        int v = graph->edge[j].v;
        int w = graph->edge[j].weight;

        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            printf("Graph contains negative weight cycle\n");
            return 0;
        }
    }

    return 1;
}

// Dijkstra's algorithm using min heap
typedef struct {
    int v;
    int dist;
} HeapNode;

typedef struct {
    int size;
    int capacity;
    int* pos;
    HeapNode* array;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->pos = (int*)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (HeapNode*)malloc(capacity * sizeof(HeapNode));
    return minHeap;
}

void swapHeapNode(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size &&
        minHeap->array[left].dist < minHeap->array[smallest].dist)
        smallest = left;

    if (right < minHeap->size &&
        minHeap->array[right].dist < minHeap->array[smallest].dist)
        smallest = right;

    if (smallest != idx) {
        minHeap->pos[minHeap->array[smallest].v] = idx;
        minHeap->pos[minHeap->array[idx].v] = smallest;

        swapHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

int isEmpty(MinHeap* minHeap) {
    return minHeap->size == 0;
}

HeapNode extractMin(MinHeap* minHeap) {
    HeapNode root = minHeap->array[0];
    HeapNode lastNode = minHeap->array[minHeap->size - 1];

    minHeap->array[0] = lastNode;
    minHeap->pos[root.v] = minHeap->size - 1;
    minHeap->pos[lastNode.v] = 0;

    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

void decreaseKey(MinHeap* minHeap, int v, int dist) {
    int i = minHeap->pos[v];
    minHeap->array[i].dist = dist;

    while (i && minHeap->array[i].dist < minHeap->array[(i - 1) / 2].dist) {
        minHeap->pos[minHeap->array[i].v] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2].v] = i;
        swapHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int isInMinHeap(MinHeap* minHeap, int v) {
    return minHeap->pos[v] < minHeap->size;
}

// Dijkstra using min heap
void dijkstra(DijkstraGraph* graph, int src, int dist[], int h[]) {
    int V = graph->V;

    for (int v = 0; v < V; v++)
        dist[v] = INT_MAX;

    dist[src] = 0;

    MinHeap* minHeap = createMinHeap(V);
    for (int v = 0; v < V; v++) {
        minHeap->array[v].v = v;
        minHeap->array[v].dist = dist[v];
        minHeap->pos[v] = v;
    }

    minHeap->size = V;

    while (!isEmpty(minHeap)) {
        HeapNode u = extractMin(minHeap);
        int uIndex = u.v;

        for (int i = 0; i < graph->array[uIndex].size; i++) {
            int v = graph->array[uIndex].head[i].dest;
            int weight = graph->array[uIndex].head[i].weight;

            // Apply Johnson’s reweighting
            weight += h[uIndex] - h[v];

            if (isInMinHeap(minHeap, v)) {
                if (dist[uIndex] != INT_MAX && dist[uIndex] + weight < dist[v]) {
                    dist[v] = dist[uIndex] + weight;
                    decreaseKey(minHeap, v, dist[v]);
                }
            }
        }
    }

    free(minHeap->array);
    free(minHeap->pos);
    free(minHeap);
}

// Johnson's algorithm
void johnsonsAlgorithm(DijkstraGraph* originalGraph) {
    int V = originalGraph->V;

    // Step 1: Create augmented graph for Bellman-Ford
    BellmanGraph* bGraph = createBellmanGraph(V + 1, V);
    int e = 0;

    for (int u = 0; u < V; u++) {
        bGraph->edge[e].u = V;
        bGraph->edge[e].v = u;
        bGraph->edge[e].weight = 0;
        e++;
    }

    for (int u = 0; u < V; u++) {
        for (int i = 0; i < originalGraph->array[u].size; i++) {
            int v = originalGraph->array[u].head[i].dest;
            int w = originalGraph->array[u].head[i].weight;
            bGraph->edge[e].u = u;
            bGraph->edge[e].v = v;
            bGraph->edge[e].weight = w;
            e++;
        }
    }

    bGraph->E = e;

    // Step 2: Run Bellman-Ford on augmented graph
    int* h = (int*)malloc(V * sizeof(int));
    if (!bellmanFord(bGraph, V, h)) {
        free(h);
        return;
    }

    // Step 3: Reweight edges
    DijkstraGraph* reweightedGraph = createDijkstraGraph(V);
    for (int u = 0; u < V; u++) {
        for (int i = 0; i < originalGraph->array[u].size; i++) {
            int v = originalGraph->array[u].head[i].dest;
            int w = originalGraph->array[u].head[i].weight;
            int newWeight = w + h[u] - h[v];
            addEdge(reweightedGraph, u, v, newWeight);
        }
    }

    // Step 4: Run Dijkstra for each node
    int dist[V][V];
    for (int u = 0; u < V; u++) {
        dijkstra(reweightedGraph, u, dist[u], h);
    }

    // Final adjustment
    for (int u = 0; u < V; u++) {
        for (int v = 0; v < V; v++) {
            dist[u][v] -= h[u] - h[v];
        }
    }

    // Print distance matrix
    printf("All-pairs shortest paths:\n     ");
    for (int i = 0; i < V; i++) printf("%6d", i);
    printf("\n");

    for (int u = 0; u < V; u++) {
        printf("%3d ", u);
        for (int v = 0; v < V; v++) {
            if (dist[u][v] == INT_MAX)
                printf("   INF");
            else
                printf("%6d", dist[u][v]);
        }
        printf("\n");
    }

    free(h);
}

// Driver program
int main() {
    int V = 6;
    DijkstraGraph* graph = createDijkstraGraph(V);

    // Add edges
    addEdge(graph, 0, 1, 5);
    addEdge(graph, 0, 2, 3);
    addEdge(graph, 1, 2, 2);
    addEdge(graph, 1, 3, 6);
    addEdge(graph, 2, 1, 1);
    addEdge(graph, 2, 4, 5);
    addEdge(graph, 3, 2, 2);
    addEdge(graph, 3, 5, 2);
    addEdge(graph, 4, 3, 1);
    addEdge(graph, 4, 5, 4);

    printf("Running Johnson’s Algorithm...\n");
    johnsonsAlgorithm(graph);

    return 0;
}






















// 1) Input:
// - Directed graph with possibly negative edge weights (but no negative cycles)
// - Each vertex has adjacency list and weight
// - Output: All-pairs shortest paths

// 2) Algorithm:
// Johnson’s Algorithm:
// - Step 1: Add source node connected to all nodes (weight 0)
// - Step 2: Run Bellman-Ford from new node to compute h(v)
// - Step 3: Reweight edges using h(u) - h(v)
// - Step 4: Run Dijkstra’s from each node on reweighted graph
// - Step 5: Adjust final distances back using h values

// 3) Time Complexity:
// Best/Avg/Worst Case: O(V * E + V * E + V * (E log V)) = O(V * E log V)
// Bellman-Ford: O(V * E), Dijkstra per node: O(E log V)

// 4) Space Complexity:
// - O(V + E), for storing graphs and distance matrix

// 5) Advantages / Disadvantages:
// + Handles negative edges unlike Dijkstra
// + Faster than Floyd-Warshall for sparse graphs
// - Slower than Floyd-Warshall (O(V^3)) for dense graphs
// - Requires careful memory management

// 6) Recurrence Relation:
// Not applicable directly — uses combination of greedy (Dijkstra) and DP (Bellman-Ford)

// 7) Summary (2 lines):
// Computes all-pairs shortest paths in graphs with negative edges.
// Combines Bellman-Ford and Dijkstra’s algorithms for efficiency.