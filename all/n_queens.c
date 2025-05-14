#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MAX 1000000

typedef struct board
{
    char **board;
} Board;


Board *createBoard(int n)
{
    Board *board = (Board *)malloc(sizeof(Board));
    board->board = (char **)malloc(sizeof(char *)*n);
    for (int k = 0; k < n; k++)
    {
        board->board[k] = (char *)malloc(sizeof(char) * n);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            board->board[i][j] = '.';
        }
    }
    return board;
}

Board *cloneBoard(Board * original, int n)
{
    Board *clone = createBoard(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            clone->board[i][j] = original->board[i][j];
        }
        
    }
    
    return clone;
}
typedef struct
{
    bool *columns;
    bool *diag1;
    bool *diag2;
    Board *board;
    Board **solution;
} NQueenSolver;

NQueenSolver *init(int n)
{
    NQueenSolver *solver;
    solver = (NQueenSolver *)malloc(sizeof(NQueenSolver));
    solver->columns = (bool *)malloc(sizeof(bool) * n);
    solver->diag1 = (bool *)malloc(sizeof(bool) * (2 * n - 1));
    solver->diag2 = (bool *)malloc(sizeof(bool) * (2 * n - 1));
    solver->solution = (Board **)malloc(sizeof(Board *) * MAX);
    solver->board = createBoard(n);
    for (int i = 0; i < 2 * n - 1; i++)
    {
        if (i < n)
        {
            solver->columns[i] = false;
        }
        solver->diag1[i] = false;
        solver->diag2[i] = false;
    }

    return solver;
}

void printSolutions(NQueenSolver * solver,int numSolution,int n)
{
    for (int i = 0; i < numSolution; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                printf("%c ", solver->solution[i]->board[j][k]);
            }
            printf("\n");
        }

        printf("-------------\n");
    }
}
void NQueenProblem(int row, NQueenSolver *solver, int n, int *numSolutions)
{
    if (row == n)
    {
        solver->solution[(*numSolutions)++] = cloneBoard(solver->board,n);
    }

    for (int column = 0; column < n; column++)
    {
        int d1 = row - column + n - 1;
        int d2 = row + column;

        if(solver->columns[column] || solver->diag1[d1] || solver->diag2[d2]) continue;

        solver->board->board[row][column]='Q';
        solver->columns[column] = solver->diag1[d1] = solver->diag2[d2] = true;

        NQueenProblem(row+1,solver,n,numSolutions);

        solver->board->board[row][column]='.';
        solver->columns[column] = solver->diag1[d1] = solver->diag2[d2] = false;
    }
}
int main(int argc, char const *argv[])
{
    int n;
    int numSolutions = 0;
    NQueenSolver *solver;
    printf("Enter n : ");
    scanf("%d", &n);

    solver = init(n);

    NQueenProblem(0,solver,n,&numSolutions);

    printSolutions(solver,numSolutions,n);

    printf("Number of solutions : %d\n", numSolutions);
    return 0;
}
