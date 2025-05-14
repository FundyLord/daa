#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 2

void addVal(int a, int b, int* c) {
    *c = a + b;
}

void subVal(int a, int b, int* c) {
    *c = a - b;
}

void strassen(int A[N][N], int B[N][N], int C[N][N]){
    int S1, S2, S3, S4, S5, S6, S7, S8, S9, S10;
    int P1, P2, P3, P4, P5, P6, P7;

    // Compute Si values
    subVal(B[0][1], B[1][1], &S1);             // S1 = B12 - B22
    addVal(A[0][0], A[0][1], &S2);             // S2 = A11 + A12
    addVal(A[1][0], A[1][1], &S3);             // S3 = A21 + A22
    subVal(B[1][0], B[0][0], &S4);             // S4 = B21 - B11
    addVal(A[0][0], A[1][1], &S5);             // S5 = A11 + A22
    addVal(B[0][0], B[1][1], &S6);             // S6 = B11 + B22
    subVal(A[0][1], A[1][1], &S7);             // S7 = A12 - A22
    addVal(B[1][0], B[1][1], &S8);             // S8 = B21 + B22
    subVal(A[0][0], A[1][0], &S9);             // S9 = A11 - A21
    addVal(B[0][0], B[0][1], &S10);            // S10 = B11 + B12

    // Compute Pi values
    P1 = A[0][0] * S1;
    P2 = S2 * B[1][1];
    P3 = S3 * B[0][0];
    P4 = A[1][1] * S4;
    P5 = S5 * S6;
    P6 = S7 * S8;
    P7 = S9 * S10;

    // Compute result matrix C
    C[0][0] = P5 + P4 - P2 + P6;
    C[0][1] = P1 + P2;
    C[1][0] = P3 + P4;
    C[1][1] = P5 + P1 - P3 - P7;
}

void printMatrix(int M[N][N]){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int A[N][N], B[N][N], C[N][N];

    printf("Enter elements of 2x2 matrix A:\n");
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            scanf("%d", &A[i][j]);

    printf("Enter elements of 2x2 matrix B:\n");
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            scanf("%d", &B[i][j]);

    clock_t start = clock();
    strassen(A, B, C);
    clock_t end = clock();

    printf("Resultant matrix C:\n");
    printMatrix(C);

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Strassen's Multiplication Time: %f seconds\n", time_taken);

    return 0;
}

