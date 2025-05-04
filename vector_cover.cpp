#include <iostream>
#include <vector>
#include <array>

#define MAX 100

using namespace std;

int graph[MAX][MAX];       // Adjacency matrix
array<bool, MAX> visited;  // To mark visited vertices
int n;                     // Number of vertices

void vertexCoverApproximation() {
    array<bool, MAX> selected = {false};
    cout << "\nApproximate Vertex Cover:\n";

    for (int u = 0; u < n; u++) {
        if (visited[u]) continue;
        for (int v = 0; v < n; v++) {
            if (graph[u][v] && !visited[v]) {
                visited[u] = true;
                visited[v] = true;
                selected[u] = true;
                selected[v] = true;
                break; // move to next u
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (selected[i])
            cout << "Vertex " << i << "\n";
    }
}

int main() {
    int edges;
    cout << "Enter number of vertices: ";
    cin >> n;
    
    cout << "Enter number of edges: ";
    cin >> edges;

    // Initialize graph with 0
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    cout << "Enter edges (u v):\n";
    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        graph[u][v] = 1;
        graph[v][u] = 1; // since it's undirected
    }

    vertexCoverApproximation();

    return 0;
}
