#include <iostream>
#include <limits.h>
#include <queue>
#include <vector>
using namespace std;

class Graph {
    int V;
    vector<vector<int>> capacity;

public:
    Graph(int vertices) : V(vertices), capacity(vertices, vector<int>(vertices, 0)) {}

    void addEdge(int u, int v, int cap) {
        capacity[u][v] = cap;
    }

    bool bfs(int source, int sink, vector<int>& parent) {
        fill(parent.begin(), parent.end(), -1);
        queue<pair<int, int>> q;
        q.push({source, INT_MAX});

        while (!q.empty()) {
            int u = q.front().first;
            int flow = q.front().second;
            q.pop();

            for (int v = 0; v < V; v++) {
                if (parent[v] == -1 && capacity[u][v] > 0) {
                    parent[v] = u;
                    int new_flow = min(flow, capacity[u][v]);
                    if (v == sink) return true;
                    q.push({v, new_flow});
                }
            }
        }
        return false;
    }

    int fordFulkerson(int source, int sink) {
        int maxFlow = 0;
        vector<int> parent(V);

        while (bfs(source, sink, parent)) {
            int flow = INT_MAX, v = sink;
            while (v != source) {
                int u = parent[v];
                flow = min(flow, capacity[u][v]);
                v = u;
            }
            v = sink;
            while (v != source) {
                int u = parent[v];
                capacity[u][v] -= flow;
                capacity[v][u] += flow;
                v = u;
            }
            maxFlow += flow;
        }
        return maxFlow;
    }
};

int main() {
    int vertices = 20; // At least 20 vertices
    Graph g(vertices);

    // Adding edges with capacities using adjacency matrix
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 15);
    g.addEdge(1, 3, 12);
    g.addEdge(2, 3, 10);
    g.addEdge(3, 4, 25);
    g.addEdge(4, 5, 20);
    g.addEdge(5, 6, 18);
    g.addEdge(6, 7, 16);
    g.addEdge(7, 8, 22);
    g.addEdge(8, 9, 14);
    g.addEdge(9, 10, 30);
    g.addEdge(10, 11, 8);
    g.addEdge(11, 12, 15);
    g.addEdge(12, 13, 20);
    g.addEdge(13, 14, 17);
    g.addEdge(14, 15, 19);
    g.addEdge(15, 16, 13);
    g.addEdge(16, 17, 24);
    g.addEdge(17, 18, 11);
    g.addEdge(18, 19, 27);
    g.addEdge(19, 0, 21);

    int source = 0, sink = 19;
    cout << "Maximum Flow: " << g.fordFulkerson(source, sink) << endl;

    return 0;
}
