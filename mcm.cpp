#include <bits/stdc++.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Function to generate random dimensions for square matrices (powers of 2)
vector<int> generateRandomDimensions(int num_matrices) {
    vector<int> dims;
    // Initial dimension (power of 2, at least 2^5 = 32 to ensure measurable time)
    int exp = rand() % 4 + 5; // Random exponent between 5 and 8 (32 to 256)
    dims.push_back(1 << exp); // e.g., 32, 64, ..., 256

    // Subsequent dimensions match to keep matrices square
    for (int i = 0; i < num_matrices; ++i) {
        dims.push_back(dims.back());
    }
    return dims;
}

// Function to generate random square matrices
void generateRandomMatrices(vector<vector<vector<double>>>& matrices, const vector<int>& dimensions) {
    for (size_t i = 0; i < dimensions.size() - 1; ++i) {
        int size = dimensions[i]; // Square matrix: size x size
        vector<vector<double>> matrix(size, vector<double>(size));
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                matrix[j][k] = (rand() % 100) / 100.0; // Random values between 0 and 1
            }
        }
        matrices.push_back(matrix);
    }
}

// Regular matrix multiplication
vector<vector<double>> regularMultiplication(const vector<vector<double>>& A, const vector<vector<double>>& B) {
    int n = A.size();
    vector<vector<double>> C(n, vector<double>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

// Helper function to add two matrices
vector<vector<double>> addMatrices(const vector<vector<double>>& A, const vector<vector<double>>& B) {
    int n = A.size();
    vector<vector<double>> result(n, vector<double>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
    return result;
}

// Helper function to subtract two matrices
vector<vector<double>> subtractMatrices(const vector<vector<double>>& A, const vector<vector<double>>& B) {
    int n = A.size();
    vector<vector<double>> result(n, vector<double>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
    return result;
}

// Strassen's Matrix Multiplication
vector<vector<double>> strassenMultiplication(const vector<vector<double>>& A, const vector<vector<double>>& B) {
    int n = A.size();
    vector<vector<double>> C(n, vector<double>(n, 0));

    // Base case: Use regular multiplication for small matrices
    if (n <= 64) {
        return regularMultiplication(A, B);
    }

    int mid = n / 2;

    // Split matrices into submatrices
    vector<vector<double>> A11(mid, vector<double>(mid)), A12(mid, vector<double>(mid)),
                          A21(mid, vector<double>(mid)), A22(mid, vector<double>(mid)),
                          B11(mid, vector<double>(mid)), B12(mid, vector<double>(mid)),
                          B21(mid, vector<double>(mid)), B22(mid, vector<double>(mid));

    for (int i = 0; i < mid; ++i) {
        for (int j = 0; j < mid; ++j) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + mid];
            A21[i][j] = A[i + mid][j];
            A22[i][j] = A[i + mid][j + mid];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + mid];
            B21[i][j] = B[i + mid][j];
            B22[i][j] = B[i + mid][j + mid];
        }
    }

    // Compute M1 to M7
    auto M1 = strassenMultiplication(A11, subtractMatrices(B12, B22));
    auto M2 = strassenMultiplication(addMatrices(A11, A12), B22);
    auto M3 = strassenMultiplication(addMatrices(A21, A22), B11);
    auto M4 = strassenMultiplication(A22, subtractMatrices(B21, B11));
    auto M5 = strassenMultiplication(addMatrices(A11, A22), addMatrices(B11, B22));
    auto M6 = strassenMultiplication(subtractMatrices(A12, A22), addMatrices(B21, B22));
    auto M7 = strassenMultiplication(subtractMatrices(A11, A21), addMatrices(B11, B12));

    // Combine results
    auto C11 = addMatrices(subtractMatrices(addMatrices(M5, M4), M2), M6);
    auto C12 = addMatrices(M1, M2);
    auto C21 = addMatrices(M3, M4);
    auto C22 = subtractMatrices(subtractMatrices(addMatrices(M5, M1), M3), M7);

    // Merge submatrices into C
    for (int i = 0; i < mid; ++i) {
        for (int j = 0; j < mid; ++j) {
            C[i][j] = C11[i][j];
            C[i][j + mid] = C12[i][j];
            C[i + mid][j] = C21[i][j];
            C[i + mid][j + mid] = C22[i][j];
        }
    }
    return C;
}

// Function to compute the optimal matrix chain multiplication using Dynamic Programming
void matrixChainOrder(const vector<int>& dims, vector<vector<int>>& m, vector<vector<int>>& s) {
    int n = dims.size() - 1;

    // Initialize m and s
    for (int i = 1; i <= n; ++i) {
        m[i][i] = 0;
    }

    for (int l = 2; l <= n; ++l) {
        for (int i = 1; i <= n - l + 1; ++i) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;

            for (int k = i; k < j; ++k) {
                int q = m[i][k] + m[k + 1][j] + dims[i - 1] * dims[k] * dims[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}

// Function to print the optimal parenthesization
void printOptimalParenthesization(const vector<vector<int>>& s, int i, int j) {
    if (i == j) {
        cout << "A" << i;
    } else {
        cout << "(";
        printOptimalParenthesization(s, i, s[i][j]);
        printOptimalParenthesization(s, s[i][j] + 1, j);
        cout << ")";
    }
}

int main() {
    srand(time(0));

    // Step 1: Generate random dimensions for square matrices
    int num_matrices = 10; // Number of matrices
    vector<int> dims = generateRandomDimensions(num_matrices);
    vector<vector<vector<double>>> matrices;

    // Step 2: Generate random square matrices
    generateRandomMatrices(matrices, dims);

    // Step 3: Perform matrix chain multiplication using Dynamic Programming
    int n = dims.size() - 1;
    vector<vector<int>> m(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> s(n + 1, vector<int>(n + 1, 0));
    matrixChainOrder(dims, m, s);

    // Step 4: Print optimal parenthesization
    cout << "Optimal Parenthesization for Matrix Chain Multiplication: ";
    printOptimalParenthesization(s, 1, n);
    cout << endl;

    // Step 5: Perform regular matrix multiplication and measure time
    auto start = high_resolution_clock::now();
    vector<vector<double>> result = matrices[0];
    for (size_t i = 1; i < matrices.size(); ++i) {
        result = regularMultiplication(result, matrices[i]);
    }
    auto end = high_resolution_clock::now();
    auto regularTime = duration_cast<microseconds>(end - start).count();
    cout << "Time for regular matrix multiplication: " << regularTime << " microseconds" << endl;

    // Step 6: Perform Strassen's matrix multiplication and measure time
    start = high_resolution_clock::now();
    result = matrices[0];
    for (size_t i = 1; i < matrices.size(); ++i) {
        result = strassenMultiplication(result, matrices[i]);
    }
    end = high_resolution_clock::now();
    auto strassenTime = duration_cast<microseconds>(end - start).count();
    cout << "Time for Strassen's matrix multiplication: " << strassenTime << " microseconds" << endl;

    return 0;
}