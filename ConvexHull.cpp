#include <bits/stdc++.h>
#include <ctime>
#include <chrono>
using namespace std;

class Point {
    public:
        int x, y;
};

// Function to determine the orientation of three points
int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;  // Collinear
    return (val > 0) ? 1 : -1; // 1 for clockwise, -1 for counterclockwise
}

// Function to calculate the squared Euclidean distance
int distanceSquared(Point p1, Point p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}
Point pivot;
bool compare(Point a, Point b) {
    int orient = orientation(pivot, a, b);
    if (orient == 0) 
        return (pow(a.x - pivot.x, 2) + pow(a.y - pivot.y, 2)) < 
               (pow(b.x - pivot.x, 2) + pow(b.y - pivot.y, 2));
    return orient == -1; 
}

int distance(Point p1, Point p2, Point p) {
    return abs((p.y - p1.y) * (p2.x - p1.x) - (p.x - p1.x) * (p2.y - p1.y));
}

// Function to find convex hull using brute-force (James March method)
vector<Point> jamesMarchConvexHull(vector<Point>& points) {
    int n = points.size();
    set<pair<int, int>> uniqueHull; // Store unique points
    vector<Point> hull;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            Point p1 = points[i], p2 = points[j];
            int pos = 0, neg = 0;

            for (int k = 0; k < n; k++) {
                if (k == i || k == j) continue;
                int orient = orientation(p1, p2, points[k]);

                if (orient > 0) pos++;
                else if (orient < 0) neg++;

                if (pos > 0 && neg > 0) break; 
            }

            if (pos == 0 || neg == 0) {
                uniqueHull.insert({p1.x, p1.y});
                uniqueHull.insert({p2.x, p2.y});
            }
        }
    }

    for (auto [x, y] : uniqueHull) {
        hull.push_back({x, y});
    }

    Point start = *min_element(hull.begin(), hull.end(), [](Point a, Point b) {
        return (a.y < b.y) || (a.y == b.y && a.x < b.x);
    });

    sort(hull.begin(), hull.end(), [&](Point a, Point b) {
        int orient = orientation(start, a, b);
        if (orient == 0) // Collinear points, keep the farthest one
            return distanceSquared(start, a) < distanceSquared(start, b);
        return orient == -1; // Counterclockwise order
    });

    vector<Point> finalHull;
    finalHull.push_back(hull[0]);

    for (int i = 1; i < hull.size(); i++) {
        while (finalHull.size() > 1 &&
               orientation(finalHull[finalHull.size() - 2], finalHull.back(), hull[i]) == 0) {
            finalHull.pop_back(); 
        }
        finalHull.push_back(hull[i]);
    }

    finalHull.push_back(finalHull[0]);

    return finalHull;
}

// Function to find convex hull using Graham's Scan
vector<Point> grahamScanConvexHull(vector<Point> points) {
    int n = points.size();
    if (n < 3) return {};

    int ymin = points[0].y, minIndex = 0;
    for (int i = 1; i < n; i++) {
        if ((points[i].y < ymin) || (points[i].y == ymin && points[i].x < points[minIndex].x)) {
            ymin = points[i].y;
            minIndex = i;
        }
    }
    swap(points[0], points[minIndex]);
    Point pivot = points[0];

    sort(points.begin() + 1, points.end(), [&](Point a, Point b) {
        int orient = orientation(pivot, a, b);
        if (orient == 0)
            return distanceSquared(pivot, a) < distanceSquared(pivot, b);
        return orient == -1;
    });

    vector<Point> hull;
    hull.push_back(points[0]);
    hull.push_back(points[1]);
    hull.push_back(points[2]);

    for (int i = 3; i < n; i++) {
        while (hull.size() > 1 && orientation(hull[hull.size() - 2], hull.back(), points[i]) != -1) {
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }
    return hull;
}

void findHull(vector<Point>& points, Point p1, Point p2, vector<Point>& hull) {
    int index = -1;
    int maxDist = 0;

    for (int i = 0; i < points.size(); i++) {
        int d = distance(p1, p2, points[i]);
        if (d > maxDist) {
            index = i;
            maxDist = d;
        }
    }

    if (index == -1) {
        hull.push_back(p1);
        return;
    }

    Point farthest = points[index];
    vector<Point> leftSet1, leftSet2;

    // Find points that are on the left side of p1-farthest
    for (Point p : points) {
        if (orientation(p1, farthest, p) == -1)
            leftSet1.push_back(p);
    }

    // Find points that are on the left side of farthest-p2
    for (Point p : points) {
        if (orientation(farthest, p2, p) == -1)
            leftSet2.push_back(p);
    }

    // Recursively find the hull on both sides
    findHull(leftSet1, p1, farthest, hull);
    findHull(leftSet2, farthest, p2, hull);
}

// Divide and Conquer Hull Algorithm
vector<Point> quickHull(vector<Point>& points) {
    if (points.size() < 3)
        return points;

    int minIndex = 0, maxIndex = 0;
    for (int i = 1; i < points.size(); i++) {
        if (points[i].x < points[minIndex].x)
            minIndex = i;
        if (points[i].x > points[maxIndex].x)
            maxIndex = i;
    }

    Point p1 = points[minIndex], p2 = points[maxIndex];
    vector<Point> hull;
    vector<Point> leftSet, rightSet;

    for (Point p : points) {
        if (orientation(p1, p2, p) == -1)
            leftSet.push_back(p);
        else if (orientation(p1, p2, p) == 1)
            rightSet.push_back(p);
    }

    findHull(leftSet, p1, p2, hull);
    findHull(rightSet, p2, p1, hull);

    pivot = hull[0];
    sort(hull.begin() + 1, hull.end(), compare);

    return hull;
}

// Main function
int main() {
    ifstream pointsFile("points.txt"); 

    if (!pointsFile) { 
        cout << "An error occurred while reading the file" << endl;
        return 1;
    }

    vector<Point> points;   
    string line;
    while(getline(pointsFile, line)) {
        stringstream ss(line);
        Point p;
        char comma;
        if (ss >> p.x >> comma >> p.y) {
            points.push_back(p);
        } else {
            cout << "Incorrect formatting";
        }
    }
    pointsFile.close();

    ofstream csvFile("hull_times.csv");
    csvFile << "Size,JamesMarchTime,GrahamScanTime,QuickHullTime" << endl;

    for (int size = 4; size <= min(100, (int)points.size()); size++) {
        vector<Point> subset(points.begin(), points.begin() + size);

        auto start1 = chrono::high_resolution_clock::now();
        vector<Point> hull1 = jamesMarchConvexHull(subset);
        auto end1 = chrono::high_resolution_clock::now();
        chrono::duration<double> diff1 = end1 - start1;

        auto start2 = chrono::high_resolution_clock::now();
        vector<Point> hull2 = grahamScanConvexHull(subset);
        auto end2 = chrono::high_resolution_clock::now();
        chrono::duration<double> diff2 = end2 - start2;

        auto start3 = chrono::high_resolution_clock::now();
        vector<Point> hull3 = quickHull(subset);
        auto end3 = chrono::high_resolution_clock::now();
        chrono::duration<double> diff3 = end3 - start3;

        csvFile << size << "," << diff1.count() << "," << diff2.count() << "," << diff3.count() << endl;
    }

    csvFile.close();
    cout << "Results saved to hull_times.csv" << endl;
    return 0;
}
