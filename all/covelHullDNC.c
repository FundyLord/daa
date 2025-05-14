#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

#define NUM 100

typedef struct {
    int x;
    int y;
} Point;

// Function to read points from file
void readIntegersFromFile(const char *filename, Point *numbers, int totalNumbers, int opt) {
    FILE *inFile = fopen(filename, "r");
    if (inFile == NULL) {
        fprintf(stderr, "Error opening file for reading.\n");
        return;
    }
    if (opt) {
        for (int i = 0; i < totalNumbers; ++i) {
            fscanf(inFile, "%d", &numbers[i].x);
        }
    } else {
        for (int i = 0; i < totalNumbers; ++i) {
            fscanf(inFile, "%d", &numbers[i].y);
        }
    }
    fclose(inFile);
}

// Function to display points
void displayPoints(Point *p, int n) {
    for (int i = 0; i < n; i++) {
        printf("Point %d : %d , %d\n", i + 1, p[i].x, p[i].y);
    }
    printf("\n");
}

// Function to compute cross product
int vectorProduct(Point A, Point B, Point C) {
    return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
}

// Function to write hull points to a CSV file for visualization
void writePointsToCSV(const char *filename, Point *points, int numPoints) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file for writing.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "X,Y\n");  
    for (int i = 0; i < numPoints; i++) {  
        fprintf(file, "%d,%d\n", points[i].x, points[i].y);  
    }  
    fclose(file);  
}

// Comparison function for sorting points by x-coordinates, then by y-coordinates
int compare(const void *a, const void *b) {  
    Point p1 = *(Point *)a;  
    Point p2 = *(Point *)b;  
    if (p1.x != p2.x) return p1.x - p2.x;
    return p1.y - p2.y;
}

// Sort points based on x-coordinates
void sortPoints(Point *points, int n) {
    qsort(points, n, sizeof(Point), compare);
}

// Function to merge two convex hulls
// Function to check if three points are collinear
int isCollinear(Point a, Point b, Point c) {
    return ((b.y - a.y) * (c.x - b.x)) == ((b.x - a.x) * (c.y - b.y));
}

// Function to merge two hulls
void mergeHulls(Point leftHull[], int leftSize, Point rightHull[], int rightSize, Point ans[], int *hullSize) {
    int leftMost = 0, rightMost = 0;

    // Find rightmost point in leftHull
    for (int i = 1; i < leftSize; i++)
        if (leftHull[i].x > leftHull[leftMost].x)
            leftMost = i;

    // Find leftmost point in rightHull
    for (int i = 1; i < rightSize; i++)
        if (rightHull[i].x < rightHull[rightMost].x)
            rightMost = i;

    // **Upper Tangent Calculation**
    int leftIndex = leftMost, rightIndex = rightMost;
    int changed;
    do {
        changed = 0;
        while (vectorProduct(rightHull[rightIndex], leftHull[leftIndex], leftHull[(leftIndex + 1) % leftSize]) < 0) {
            leftIndex = (leftIndex + 1) % leftSize;
            changed = 1;
        }
        while (vectorProduct(leftHull[leftIndex], rightHull[rightIndex], rightHull[(rightIndex - 1 + rightSize) % rightSize]) > 0) {
            rightIndex = (rightIndex - 1 + rightSize) % rightSize;
            changed = 1;
        }
    } while (changed);

    // **Lower Tangent Calculation**
    int lowerLeft = leftMost, lowerRight = rightMost;
    do {
        changed = 0;
        while (vectorProduct(leftHull[lowerLeft], rightHull[lowerRight], rightHull[(lowerRight + 1) % rightSize]) < 0) {
            lowerRight = (lowerRight + 1) % rightSize;
            changed = 1;
        }
        while (vectorProduct(rightHull[lowerRight], leftHull[lowerLeft], leftHull[(lowerLeft - 1 + leftSize) % leftSize]) > 0) {
            lowerLeft = (lowerLeft - 1 + leftSize) % leftSize;
            changed = 1;
        }
    } while (changed);

    // **Merging Hulls Without Redundant Points**
    int index = 0;
    
    // Left hull points from upper tangent to lower tangent
    int i = leftIndex;
    do {
        ans[index++] = leftHull[i];
        i = (i + 1) % leftSize;
    } while (i != lowerLeft);
    
    ans[index++] = leftHull[lowerLeft];

    // Right hull points from lower tangent to upper tangent
    i = lowerRight;
    do {
        ans[index++] = rightHull[i];
        i = (i + 1) % rightSize;
    } while (i != rightIndex);

    ans[index++] = rightHull[rightIndex];

    *hullSize = index;

    // **Remove Interior Points After Merging**
    Point temp[*hullSize];
    int newSize = 0;

    for (int i = 0; i < *hullSize; i++) {
        while (newSize >= 2 && vectorProduct(temp[newSize - 2], temp[newSize - 1], ans[i]) <= 0) {
            newSize--; // Remove last point if it makes a non-left turn
        }
        temp[newSize++] = ans[i];
    }

    // Copy back the cleaned hull
    *hullSize = newSize;
    for (int i = 0; i < newSize; i++) {
        ans[i] = temp[i];
    }
}



// Recursive function to compute Convex Hull using Divide and Conquer
void ConvexHullUsingDnC(Point points[], int n, Point ans[], int *hullSize) {
    if (n <= 3) {  // Base case: if 3 or fewer points, return as hull
        for (int i = 0; i < n; i++)
            ans[i] = points[i];
        *hullSize = n;
        return;
    }

    // Split points into left and right halves
    int mid = n / 2;
    Point leftHull[mid], rightHull[n - mid];
    int leftSize, rightSize;

    // Recursively compute convex hull for left and right sets
    ConvexHullUsingDnC(points, mid, leftHull, &leftSize);
    ConvexHullUsingDnC(points + mid, n - mid, rightHull, &rightSize);

    // Merge both convex hulls
    mergeHulls(leftHull, leftSize, rightHull, rightSize, ans, hullSize);
}
void benchmarkConvexHull(Point *points) {
    FILE *file = fopen("DNC_result.csv", "w");
    if (!file) {
        fprintf(stderr, "Error: Could not open file for writing.\n");
        return;
    }
    fprintf(file, "NumPoints,DNC Time\n");

    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency);

    for (int i = 4; i <= NUM; i++) {
        Point answer[NUM];
        int required = 0;
        QueryPerformanceCounter(&start);
        ConvexHullUsingDnC(points, i, answer, &required);
        QueryPerformanceCounter(&end);
        double timeTaken = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
        fprintf(file, "%d,%lf\n", i, timeTaken);
        printf("Computed hull for %d points in %lf seconds\n", i, timeTaken);
    }
    fclose(file);
}
int main() {
    Point *points = (Point *)malloc(sizeof(Point) * NUM);
    Point answer[NUM] = {0};
    int required = 0;

    // Read points from files
    readIntegersFromFile("random_pointsX.txt", points, NUM, 1);
    readIntegersFromFile("random_pointsY.txt", points, NUM, 0);

    // Sort points based on x-coordinates
    sortPoints(points, NUM);
    benchmarkConvexHull(points);

    free(points);
    return 0;
}
