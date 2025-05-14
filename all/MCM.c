#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <math.h>
#define MAX 50

int m[MAX][MAX];
int s[MAX][MAX];

typedef struct {
    int row;
    int col;
    long long **matrix;
} Matrix;

Matrix *createMatrix(int r, int c)
{
    Matrix *m = (Matrix *)malloc(sizeof(Matrix));
    m->row = r;
    m->col = c;

    m->matrix = (long long **)malloc(sizeof(long long *) * m->row);
    for (int i = 0; i < m->row; i++)
    {
        m->matrix[i] = (long long *)malloc(sizeof(long long) * m->col);
    }

    return m;
}

void fillMatrix(Matrix *m)
{
    int r = m->row;
    int c = m->col;

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            int random = rand() % 100;
            m->matrix[i][j] = random;
        }
    }
}

int *generateDimensions(int n)
{
    int *p = (int *)malloc(sizeof(int) * (n + 1));

    for (int i = 0; i < n + 1; i++)
    {
        int random = 1 + rand() % 6;
        double power = pow(2, random);
        p[i] = (int)power;
    }

    return p;
}

Matrix **createMatrixChain(int *p, int n)
{
    Matrix **chain = (Matrix **)malloc(sizeof(Matrix *) * n);

    for (int i = 0; i < n; i++)
    {
        chain[i] = createMatrix(p[i], p[i + 1]);
        fillMatrix(chain[i]);
    }

    return chain;
}

void printMatrix(Matrix *m)
{
    printf("Dimensions : %d x %d\n", m->row, m->col);
    for (int i = 0; i < m->row; i++)
    {
        for (int j = 0; j < m->col; j++)
        {
            printf("%6lld ", m->matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void printDimensions(int *p, int n)
{
    printf("Matrix dimensions array: ");
    for (int i = 0; i < n + 1; i++)
    {
        printf("%d ", p[i]);
    }
    printf("\n\n");
}

void printMatrixChain(Matrix **chain, int n)
{
    for (int i = 0; i < n; i++)
    {
        printMatrix(chain[i]);
    }
    printf("\n");
}

void printOptimalParenthesis(int s[][100], int i, int j)
{
    if (i == j)
    {
        printf(" M%d ", i);
    }
    else
    {
        printf("(");
        printOptimalParenthesis(s, i, s[i][j]);
        printOptimalParenthesis(s, s[i][j] + 1, j);
        printf(")");
    }
}

int MatrixChainMultiplication(int *p, int n)
{
    int i, j, k, length;
    int q;
    for (i = 0; i < n; i++)
    {
        m[i][i] = 0;
    }

    for (length = 2; length <= n; length++)
    {
        for (i = 0; i < n - length + 1; i++)
        {
            j = i + length - 1;
            m[i][j] = INT_MAX;
            for (k = i; k < j; k++)
            {
                q = m[i][k] + m[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
                if (m[i][j] > q)
                {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    printf("COST TABLE :\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%5d ", m[i][j]);
        }
        printf("\n");
    }

    printf("SPLIT TABLE :\n");
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - 1; j++)
        {
            printf("%2d ", s[i][j]);
        }
        printf("\n");
    }

    printf("Optimal Parenthesis : ");
    printOptimalParenthesis(s, 0, n - 1);
    printf("\n");

    return m[0][n - 1];
}

Matrix *multiply(Matrix *A, Matrix *B)
{
    Matrix *C = createMatrix(A->row, B->col);

    for (int i = 0; i < C->row; i++)
    {
        for (int j = 0; j < C->col; j++)
        {
            C->matrix[i][j] = 0;
            for (int k = 0; k < A->col; k++)
            {
                C->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
            }
        }
    }
    return C;
}

Matrix *multiplyChain(Matrix **chain, int s[][MAX], int i, int j)
{
    if (i == j)
        return chain[i];
    else
    {
        int k = s[i][j];
        Matrix *left = multiplyChain(chain, s, i, k);
        Matrix *right = multiplyChain(chain, s, k + 1, j);
        return multiply(left, right);
    }
}

int main(int argc, char const *argv[])
{
    Matrix **chain;
    int n;
    int *p;

    srand(time(NULL));

    printf("Enter number of matrices in chain : ");
    scanf("%d", &n);

    p = generateDimensions(n);
    printDimensions(p, n);

    chain = createMatrixChain(p, n);
    printMatrixChain(chain, n);

    int optimal = MatrixChainMultiplication(p, n);
    printf("Optimal Multiplications : %d\n", optimal);

    Matrix *finalResult = multiplyChain(chain, s, 0, n - 1);
    printf("Final Matrix : \n");
    printMatrix(finalResult);

    

    return 0;
}

