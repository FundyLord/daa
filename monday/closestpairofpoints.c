#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Define a Point structure
typedef struct {
    double x;
    double y;
} Point;

// Function to compute Euclidean distance between two points
double distance(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) +
                (p1.y - p2.y) * (p1.y - p2.y));
}

// Comparator for sorting points by x-coordinate
int compareX(const void* a, const void* b) {
    Point* p1 = (Point*)a;
    Point* p2 = (Point*)b;
    if (p1->x < p2->x) return -1;
    if (p1->x > p2->x) return 1;
    return 0;
}

// Comparator for sorting points by y-coordinate
int compareY(const void* a, const void* b) {
    Point* p1 = (Point*)a;
    Point* p2 = (Point*)b;
    if (p1->y < p2->y) return -1;
    if (p1->y > p2->y) return 1;
    return 0;
}

// Function to find the minimum distance in the strip
double stripClosest(Point strip[], int size, double d) {
    double minDist = d;

    // Sort the strip by y-coordinate
    qsort(strip, size, sizeof(Point), compareY);

    // Compare each point with the next few (up to 6) points
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < minDist; ++j) {
            double dist = distance(strip[i], strip[j]);
            if (dist < minDist) {
                minDist = dist;
            }
        }
    }

    return minDist;
}

// Recursive function to find the minimum distance
double minDistUtil(Point points[], int left, int right) {
    // Base case: brute force for 2 or fewer points
    if (right - left <= 2) {
        double minDist = 1e9;
        for (int i = left; i < right; ++i) {
            for (int j = i + 1; j < right; ++j) {
                double dist = distance(points[i], points[j]);
                if (dist < minDist) {
                    minDist = dist;
                }
            }
        }
        return minDist;
    }

    // Find the midpoint
    int mid = (left + right) / 2;
    double midX = points[mid].x;

    // Recursively find the minimum distances in left and right halves
    double dl = minDistUtil(points, left, mid);
    double dr = minDistUtil(points, mid, right);
    double d = (dl < dr) ? dl : dr;

    // Build the strip of points within distance d from the midline
    Point strip[right - left];
    int k = 0;
    for (int i = left; i < right; ++i) {
        if (fabs(points[i].x - midX) < d) {
            strip[k++] = points[i];
        }
    }

    // Find the minimum distance in the strip
    double stripDist = stripClosest(strip, k, d);

    return (d < stripDist) ? d : stripDist;
}

// Main function to find the closest pair of points
double minDistance(Point points[], int n) {
    // Sort points by x-coordinate
    qsort(points, n, sizeof(Point), compareX);

    return minDistUtil(points, 0, n);
}

// Entry point
int main() {
    Point points[] = {{-1, -2}, {0, 0}, {1, 2}, {2, 3}};
    int n = sizeof(points) / sizeof(points[0]);

    double res = minDistance(points, n);

    // Output the result with 6 decimal places
    printf("%.6f\n", res);

    return 0;
}










//gcc -std=c99 -o closest_pair closest_pair.c -lm
//./closest_pair











// 1) Input:
// - Array of Point structs with x and y coordinates
// - n: number of points

// 2) Algorithm:
// Divide and Conquer (Closest Pair)
// - Sort points by x-coordinate
// - Recursively split into left/right halves
// - Find closest pair in each half
// - Check strip around midline for closer pairs (up to 6 comparisons per point)

// 3) Time Complexity:
// Best/Avg/Worst Case: O(n log n)
// Sorting = O(n log n), recursion T(n) = 2T(n/2) + O(n), merging strip = O(n)

// 4) Space Complexity:
// - Call stack depth: O(log n) due to recursion
// - Strip array: O(n)
// Total: O(n)

// 5) Advantages / Disadvantages:
// + Fast asymptotic time using divide and conquer
// + Beats brute-force O(n^2)
// - Requires sorting and extra memory for strip
// - Slightly more complex than naive approach

// 6) Recurrence Relation:
// T(n) = 2T(n/2) + O(n) => T(n) = O(n log n)

// 7) Summary (2 lines):
// Solves closest pair problem efficiently using divide and conquer.
// Runs in O(n log n) time and uses O(n) space due to recursion and strip processing.