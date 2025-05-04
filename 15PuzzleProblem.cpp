#include <bits/stdc++.h>
using namespace std;

#define N 4

// Goal state
int goal[N][N] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9,10,11,12},
    {13,14,15, 0}
};

// Directions: up, down, left, right
int rowDir[] = {-1, 1, 0, 0};
int colDir[] = {0, 0, -1, 1};
string dirName[] = {"Up", "Down", "Left", "Right"};

// Structure to store the puzzle node
struct Node {
    vector<vector<int>> mat;
    int x, y; // blank tile coordinates
    int cost; // heuristic + depth
    int level;
    string path;

    bool operator>(const Node &other) const {
        return cost > other.cost;
    }
};

// Manhattan distance heuristic
int calculateHeuristic(vector<vector<int>> &mat) {
    int dist = 0;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (mat[i][j] != 0) {
                int value = mat[i][j];
                int goalRow = (value - 1) / N;
                int goalCol = (value - 1) % N;
                dist += abs(i - goalRow) + abs(j - goalCol);
            }
    return dist;
}

// Check if the position is within bounds
bool isSafe(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}

// Convert matrix to string for visited state tracking
string matrixToString(vector<vector<int>> &mat) {
    string s;
    for (auto &row : mat)
        for (int val : row)
            s += to_string(val) + ",";
    return s;
}

// Print matrix
void printMatrix(vector<vector<int>> &mat) {
    for (auto &row : mat) {
        for (int val : row)
            cout << val << "\t";
        cout << endl;
    }
    cout << "------------------" << endl;
}

void solve(vector<vector<int>> &initial, int x, int y) {
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    set<string> visited;

    Node root = {initial, x, y, calculateHeuristic(initial), 0, ""};
    pq.push(root);
    visited.insert(matrixToString(initial));

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        // Goal state found
        if (calculateHeuristic(current.mat) == 0) {
            cout << "Path to solution:\n";
            cout << "(Start)\n";
            printMatrix(initial);
            vector<vector<int>> temp = initial;
            int cx = x, cy = y;

            for (char move : current.path) {
                int dir = move - '0';
                int nx = cx + rowDir[dir];
                int ny = cy + colDir[dir];
                swap(temp[cx][cy], temp[nx][ny]);
                cout << "(" << dirName[dir] << ")\n";
                printMatrix(temp);
                cx = nx; cy = ny;
            }

            cout << "Total moves: " << current.level << endl;
            return;
        }

        for (int i = 0; i < 4; ++i) {
            int newX = current.x + rowDir[i];
            int newY = current.y + colDir[i];

            if (isSafe(newX, newY)) {
                vector<vector<int>> newMat = current.mat;
                swap(newMat[current.x][current.y], newMat[newX][newY]);

                string matStr = matrixToString(newMat);
                if (visited.count(matStr)) continue;

                int heuristic = calculateHeuristic(newMat);
                Node child = {newMat, newX, newY, heuristic + current.level + 1, current.level + 1, current.path + to_string(i)};
                pq.push(child);
                visited.insert(matStr);
            }
        }
    }

    cout << "No solution found.\n";
}

int main() {
    vector<vector<int>> initial = {
        {1, 2, 3, 4},
        {5, 6, 7, 0},
        {9, 10, 11, 8},
        {13, 14, 15, 12}
    };

    int x = 1, y = 2; // position of blank tile (0)
    solve(initial, x, y);

    return 0;
}

