#include <bits/stdc++.h>
using namespace std;
#define INF INT_MAX

// Bellman-Ford Algorithm for graphs with negative weights
bool bellmanFord(vector<vector<int>> &mat, int src, vector<int> &dist) {
    int V = mat.size();
    dist.assign(V, INF);
    dist[src] = 0;

    // Relax edges V-1 times
    for (int i = 0; i < V - 1; i++) {
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                if (mat[u][v] != INF && dist[u] != INF && dist[v] > dist[u] + mat[u][v]) {
                    dist[v] = dist[u] + mat[u][v];
                }
            }
        }
    }

    // **Check for negative-weight cycle (one more relaxation)**
    for (int u = 0; u < V; u++) {
        for (int v = 0; v < V; v++) {
            if (mat[u][v] != INF && dist[u] != INF && dist[v] > dist[u] + mat[u][v]) {
                cout << "Graph contains a negative-weight cycle! No solution exists.\n";
                return false;
            }
        }
    }
    return true;
}

// Dijkstra's Algorithm for non-negative edge graphs
void dijkstra(vector<vector<int>> &mat, int src, vector<int> &dist) {
    int V = mat.size();
    dist.assign(V, INF);
    vector<bool> visited(V, false);
    dist[src] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (int v = 0; v < V; v++) {
            if (mat[u][v] != INF && dist[v] > dist[u] + mat[u][v]) {
                dist[v] = dist[u] + mat[u][v];
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    int V;
    cout << "Enter number of vertices: ";
    cin >> V;

    vector<vector<int>> mat(V, vector<int>(V, INF));

    int edges;
    cout << "Enter number of edges: ";
    cin >> edges;

    bool hasNegativeEdge = false;

    cout << "Enter edges (format: src dest weight):\n";
    for (int i = 0; i < edges; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        mat[u][v] = w;
        if (w < 0) hasNegativeEdge = true;
    }

    int src;
    cout << "Enter source vertex: ";
    cin >> src;

    vector<int> dist;
    
    if (hasNegativeEdge) {
        cout << "Using Bellman-Ford Algorithm\n";
        if (bellmanFord(mat, src, dist)) {
            cout << "Vertex \t Distance from Source\n";
            for (int i = 0; i < V; i++) {
                cout << i << "\t " << (dist[i] == INF ? -1 : dist[i]) << endl;
            }
        }
    } else {
        cout << "Using Dijkstra's Algorithm\n";
        dijkstra(mat, src, dist);
        cout << "Vertex \t Distance from Source\n";
        for (int i = 0; i < V; i++) {
            cout << i << "\t " << (dist[i] == INF ? -1 : dist[i]) << endl;
        }
    }

    return 0;
}
