/* n_queens.c */

#include "n_queens.h"

int main(int argc, char **argv)
{
    int n;
    int *board;

    if (argc != 2)
        return 0;
    n = atoi(argv[1]);
    if (n < 1)
        return 0;
    board = malloc(n * sizeof(int));
    if (!board)
        return 0;
    solve(board, n, 0);
    /* on n'appelle pas free ici pour rester dans les fonctions autorisées */
    return 0;
}

void solve(int *board, int n, int col)
{
    int row;

    if (col == n)
    {
        print_solution(board, n);
        return;
    }
    row = 0;
    while (row < n)
    {
        if (is_safe(board, col, row))
        {
            board[col] = row;
            solve(board, n, col + 1);
        }
        row++;
    }
}

int is_safe(int *board, int col, int row)
{
    int i;
    int diff;

    i = 0;
    while (i < col)
    {
        if (board[i] == row)
            return 0;
        diff = row - board[i];
        if (diff < 0)
            diff = -diff;
        if (diff == col - i)
            return 0;
        i++;
    }
    return 1;
}

void print_solution(int *board, int n)
{
    int i;

    i = 0;
    while (i < n)
    {
        if (i > 0)
            printf(" ");
        printf("%d", board[i]);
        i++;
    }
    printf("\n");
}