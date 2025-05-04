#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <ctime>
#include <chrono>
#include <random>
#include <fstream>

using namespace std;
using namespace chrono;

struct Edge {
    int src, dest, weight;
};

struct Graph {
    int V, E;
    vector<Edge> edges;
};

// DSUF (Disjoint Set Union Find) implementation
struct DSUF {
    vector<int> parent, rank;
    DSUF(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    
    int find(int v) {
        if (parent[v] != v)
            parent[v] = find(parent[v]);
        return parent[v];
    }
    
    void unionSets(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) {
            if (rank[rootU] > rank[rootV]) parent[rootV] = rootU;
            else if (rank[rootU] < rank[rootV]) parent[rootU] = rootV;
            else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
};

// Kruskal's Algorithm
vector<Edge> kruskalMST(Graph &graph) {
    vector<Edge> result;
    sort(graph.edges.begin(), graph.edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });
    DSUF dsuf(graph.V);
    for (auto &edge : graph.edges) {
        if (dsuf.find(edge.src) != dsuf.find(edge.dest)) {
            result.push_back(edge);
            dsuf.unionSets(edge.src, edge.dest);
        }
    }
    return result;
}

// Prim's Algorithm
vector<Edge> primMST(Graph &graph) {
    vector<Edge> result;
    vector<bool> inMST(graph.V, false);
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> pq;
    inMST[0] = true;
    for (auto &edge : graph.edges) {
        if (edge.src == 0 || edge.dest == 0)
            pq.push({edge.weight, {edge.src, edge.dest}});
    }
    while (!pq.empty()) {
        auto [w, e] = pq.top(); pq.pop();
        int u = e.first, v = e.second;
        if (!inMST[v]) {
            inMST[v] = true;
            result.push_back({u, v, w});
            for (auto &edge : graph.edges) {
                if ((edge.src == v || edge.dest == v) && !inMST[edge.dest])
                    pq.push({edge.weight, {edge.src, edge.dest}});
            }
        }
    }
    return result;
}

// Generate a random graph
Graph generateRandomGraph(int V, int E) {
    Graph graph = {V, E, {}};
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 100);
    for (int i = 0; i < E; i++) {
        int u = rand() % V;
        int v = rand() % V;
        while (u == v) v = rand() % V;
        int w = dist(gen);
        graph.edges.push_back({u, v, w});
    }
    return graph;
}

// Utility function to print MST
void printMST(vector<Edge> &mst) {
    int totalWeight = 0;
    for (auto &edge : mst) {
        cout << edge.src << " - " << edge.dest << " : " << edge.weight << endl;
        totalWeight += edge.weight;
    }
    cout << "Total Weight: " << totalWeight << endl;
}

int main() {
    vector<int> sizes = {8,15,20,30,40,50,100,200,300,400,500}; // Increased graph sizes for measurable execution time
    ofstream file("mst_time_results.csv");
    file << "Graph Size, Kruskal Time (microseconds), Prim Time (microseconds)\n";
    
    for (int V : sizes) {
        int E = V * (V - 1) / 4;
        Graph graph = generateRandomGraph(V, E);
        
        auto start = high_resolution_clock::now();
        vector<Edge> kruskalMSTResult = kruskalMST(graph);
        auto stop = high_resolution_clock::now();
        auto durationKruskal = duration_cast<microseconds>(stop - start);
        
        start = high_resolution_clock::now();
        vector<Edge> primMSTResult = primMST(graph);
        stop = high_resolution_clock::now();
        auto durationPrim = duration_cast<microseconds>(stop - start);
        
        file << V << ", " << durationKruskal.count() << ", " << durationPrim.count() << "\n";
        
        cout << "Kruskal's MST for Graph Size " << V << "\n";
        printMST(kruskalMSTResult);
        cout << "\nPrim's MST for Graph Size " << V << "\n";
        printMST(primMSTResult);
        cout << "--------------------------------------\n";
    }
    
    file.close();
    cout << "MST computation complete. Results saved to mst_time_results.csv" << endl;
    return 0;
}

