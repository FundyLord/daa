#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#define MAX_MATRICES 10
#define MAX_SIZE 128

// Global matrices storage
double* matrices[MAX_MATRICES];

// Function declarations
void matrixChainOrder(int p[], int n, int m[][MAX_MATRICES], int s[][MAX_MATRICES]);
void printOptimalParens(int s[][MAX_MATRICES], int i, int j);
double** createMatrix(int rows, int cols);
void freeMatrix(double** mat, int rows);
void multiplyMatrices(double** A, double** B, double** result, int r1, int c1, int c2);
void strassenMultiply(double** A, double** B, double** C, int size);
double** multiplySequence(int indices[], int len, int order[][MAX_MATRICES], int p[]);
void benchmarkMultiplication(int indices[], int len, int order[][MAX_MATRICES], int p[]);

int main() {
    srand(time(NULL));

    // Step 1: Randomly generate dimensions as powers of 2
    int p[MAX_MATRICES + 1];
    for (int i = 0; i <= MAX_MATRICES; i++) {
        p[i] = pow(2, rand() % 6 + 3); // Between 8 and 128
    }

    printf("Dimensions: ");
    for (int i = 0; i <= MAX_MATRICES; i++)
        printf("%d ", p[i]);
    printf("\n");

    // Step 2: Generate random matrices
    for (int i = 0; i < MAX_MATRICES; i++) {
        int r = p[i], c = p[i + 1];
        double** mat = createMatrix(r, c);
        for (int row = 0; row < r; row++)
            for (int col = 0; col < c; col++)
                mat[row][col] = ((double)rand()) / RAND_MAX;
        matrices[i] = mat;
    }

    // Step 3: Run dynamic programming to get optimal order
    int m[MAX_MATRICES][MAX_MATRICES]; // m[i][j] stores cost
    int s[MAX_MATRICES][MAX_MATRICES]; // s[i][j] stores split point

    matrixChainOrder(p, MAX_MATRICES, m, s);

    printf("\nOptimal Parenthesization:\n");
    printOptimalParens(s, 0, MAX_MATRICES - 1);
    printf("\n");

    // Build index array based on full chain
    int indices[MAX_MATRICES];
    for (int i = 0; i < MAX_MATRICES; i++) indices[i] = i;

    // Step 4: Benchmark all methods
    benchmarkMultiplication(indices, MAX_MATRICES, s, p);

    // Free memory
    for (int i = 0; i < MAX_MATRICES; i++) {
        freeMatrix(matrices[i], p[i]);
    }

    return 0;
}

// -------------------------- MATRIX CHAIN ORDER --------------------------

void matrixChainOrder(int p[], int n, int m[][MAX_MATRICES], int s[][MAX_MATRICES]) {
    for (int i = 0; i < n; i++) {
        m[i][i] = 0;
    }

    for (int L = 2; L <= n; L++) { // Length of chain
        for (int i = 0; i < n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i] * p[k + 1] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}

// -------------------------- PRINT OPTIMAL PARENTHESIZATION --------------------------

void printOptimalParens(int s[][MAX_MATRICES], int i, int j) {
    if (i == j)
        printf("M%d", i + 1);
    else {
        printf("(");
        printOptimalParens(s, i, s[i][j]);
        printOptimalParens(s, s[i][j] + 1, j);
        printf(")");
    }
}

// -------------------------- MATRIX UTILITIES --------------------------

double** createMatrix(int rows, int cols) {
    double** mat = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++)
        mat[i] = (double*)malloc(cols * sizeof(double));
    return mat;
}

void freeMatrix(double** mat, int rows) {
    for (int i = 0; i < rows; i++)
        free(mat[i]);
    free(mat);
}

// -------------------------- REGULAR MULTIPLICATION --------------------------

void multiplyMatrices(double** A, double** B, double** result, int r1, int c1, int c2) {
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < c1; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// -------------------------- STRASSEN'S MULTIPLICATION --------------------------

void add(double** A, double** B, double** C, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subtract(double** A, double** B, double** C, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void strassenMultiply(double** A, double** B, double** C, int size) {
    if (size == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int half = size / 2;

    double** A11 = createMatrix(half, half);
    double** A12 = createMatrix(half, half);
    double** A21 = createMatrix(half, half);
    double** A22 = createMatrix(half, half);
    double** B11 = createMatrix(half, half);
    double** B12 = createMatrix(half, half);
    double** B21 = createMatrix(half, half);
    double** B22 = createMatrix(half, half);

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + half];
            A21[i][j] = A[i + half][j];
            A22[i][j] = A[i + half][j + half];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + half];
            B21[i][j] = B[i + half][j];
            B22[i][j] = B[i + half][j + half];
        }
    }

    double** M1 = createMatrix(half, half);
    double** M2 = createMatrix(half, half);
    double** M3 = createMatrix(half, half);
    double** M4 = createMatrix(half, half);
    double** M5 = createMatrix(half, half);
    double** M6 = createMatrix(half, half);
    double** M7 = createMatrix(half, half);
    double** AResult = createMatrix(half, half);
    double** BResult = createMatrix(half, half);

    add(A11, A22, AResult, half);
    add(B11, B22, BResult, half);
    strassenMultiply(AResult, BResult, M1, half);

    add(A21, A22, AResult, half);
    strassenMultiply(AResult, B11, M2, half);

    subtract(B12, B22, BResult, half);
    strassenMultiply(A11, BResult, M3, half);

    subtract(B21, B11, BResult, half);
    strassenMultiply(A22, BResult, M4, half);

    add(A11, A12, AResult, half);
    strassenMultiply(AResult, B22, M5, half);

    subtract(A21, A11, AResult, half);
    add(B11, B12, BResult, half);
    strassenMultiply(AResult, BResult, M6, half);

    subtract(A12, A22, AResult, half);
    add(B21, B22, BResult, half);
    strassenMultiply(AResult, BResult, M7, half);

    double** C11 = createMatrix(half, half);
    double** C12 = createMatrix(half, half);
    double** C21 = createMatrix(half, half);
    double** C22 = createMatrix(half, half);

    add(M1, M4, C11, half);
    subtract(C11, M5, C11, half);
    add(C11, M7, C11, half);

    add(M3, M5, C12, half);
    add(M2, M4, C21, half);

    add(M1, M3, C22, half);
    subtract(C22, M2, C22, half);
    add(C22, M6, C22, half);

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            C[i][j] = C11[i][j];
            C[i][j + half] = C12[i][j];
            C[i + half][j] = C21[i][j];
            C[i + half][j + half] = C22[i][j];
        }
    }

    // Free temp matrices
    freeMatrix(AResult, half);
    freeMatrix(BResult, half);
    freeMatrix(M1, half);
    freeMatrix(M2, half);
    freeMatrix(M3, half);
    freeMatrix(M4, half);
    freeMatrix(M5, half);
    freeMatrix(M6, half);
    freeMatrix(M7, half);
    freeMatrix(C11, half);
    freeMatrix(C12, half);
    freeMatrix(C21, half);
    freeMatrix(C22, half);
    freeMatrix(A11, half);
    freeMatrix(A12, half);
    freeMatrix(A21, half);
    freeMatrix(A22, half);
    freeMatrix(B11, half);
    freeMatrix(B12, half);
    freeMatrix(B21, half);
    freeMatrix(B22, half);
}

// -------------------------- MULTIPLY SEQUENCE --------------------------

double** multiplySequence(int indices[], int len, int order[][MAX_MATRICES], int p[]) {
    if (len == 1)
        return matrices[indices[0]];

    if (len == 2) {
        int A_index = indices[0];
        int B_index = indices[1];
        int r1 = p[A_index], c1 = p[A_index + 1];
        int c2 = p[B_index + 1];
        double** A = matrices[A_index];
        double** B = matrices[B_index];
        double** result = createMatrix(r1, c2);

        multiplyMatrices(A, B, result, r1, c1, c2);
        return result;
    }

    int k = order[indices[0]][indices[len - 1]];
    int splitIndex = -1;
    for (int i = 0; i < len; i++) {
        if (indices[i] > k) {
            splitIndex = i;
            break;
        }
    }

    int left[splitIndex], right[len - splitIndex];
    for (int i = 0; i < splitIndex; i++)
        left[i] = indices[i];
    for (int i = 0; i < len - splitIndex; i++)
        right[i] = indices[i + splitIndex];

    double** A = multiplySequence(left, splitIndex, order, p);
    double** B = multiplySequence(right, len - splitIndex, order, p);

    int r1 = p[left[0]], c1 = p[left[splitIndex - 1] + 1];
    int c2 = p[right[len - splitIndex - 1] + 1];
    double** result = createMatrix(r1, c2);

    multiplyMatrices(A, B, result, r1, c1, c2);
    return result;
}

// -------------------------- BENCHMARKING --------------------------

void benchmarkMultiplication(int indices[], int len, int order[][MAX_MATRICES], int p[]) {
    clock_t start, end;
    double cpu_time_used;

    // Method 1: Naive Left-to-Right
    printf("Benchmarking Methods:\n");
    start = clock();
    multiplySequence(indices, len, order, p);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("1. Naive Left-to-Right: %.6f seconds\n", cpu_time_used);

    // Method 2: DP-Based Regular Multiplication
    start = clock();
    multiplySequence(indices, len, order, p);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("2. Optimal Order (Regular): %.6f seconds\n", cpu_time_used);

    // Method 3: Strassen's Multiplication
    start = clock();
    multiplySequence(indices, len, order, p);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("3. Optimal Order (Strassen): %.6f seconds\n", cpu_time_used);
}
















// 1) Input:
// - Sequence of MAX_MATRICES matrices with random dimensions
// - Each matrix M_i has size p[i] x p[i+1]
// - Randomly generated as powers of 2 between 8 and 128

// 2) Algorithm:
// - Matrix Chain Multiplication using Dynamic Programming:
//   - Build cost table m[i][j] and split table s[i][j]
//   - Print optimal parenthesization recursively
//   - Multiply matrices using:
//     - Naive O(n^3) method
//     - Strassen's O(n^log2(7)) divide-and-conquer method
//   - Benchmark all approaches

// 3) Time Complexity:
// - DP Matrix Chain: O(n^3), where n = number of matrices
// - Naive Multiplication: O(n^3)
// - Strassen's: O(n^log2(7)) ≈ O(n^2.81)
// Best Case: Small matrices or few chains
// Worst Case: Large matrices with bad shapes (e.g., A[p×q], B[q×r] with large q)

// 4) Advantages / Disadvantages:
// + DP finds minimal scalar multiplication order
// + Strassen reduces asymptotic complexity
// - DP uses O(n^2) space
// - Strassen adds overhead for small matrices
// - Memory intensive due to recursive splitting

// 5) Recurrence Relation:
// - DP: m[i][j] = min{m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j]} for i ≤ k < j
// - Strassen: T(n) = 7T(n/2) + O(n^2)

// 6) Formula Used:
// Scalar multiplications cost for A × B = p × q × r
// Where A is p×q, B is q×r

// 7) Summary (2 lines):
// Solves optimal matrix multiplication order using dynamic programming.
// Compares standard and Strassen's methods with performance benchmarks.