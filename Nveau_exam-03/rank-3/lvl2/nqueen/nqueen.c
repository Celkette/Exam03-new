#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

#define N 8 // Modifier cette valeur pour d'autres tailles d'échiquier

void print_solution(int board[N]) {
    char output[N * (N + 1)];
    int index = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            output[index++] = (board[i] == j) ? 'D' : '.';
        }
        output[index++] = '\n';
    }
    write(1, output, index);
}

bool is_safe(int board[N], int row, int col) {
    for (int i = 0; i < row; i++) {
        if (board[i] == col || board[i] - i == col - row || board[i] + i == col + row)
            return false;
    }
    return true;
}

void solve_n_queens(int board[N], int row) {
    if (row == N) {
        print_solution(board);
        write(1, "\n", 1);
        return;
    }
    for (int col = 0; col < N; col++) {
        if (is_safe(board, row, col)) {
            board[row] = col;
            solve_n_queens(board, row + 1);
        }
    }
}

int main(void) {
    int board[N];
    solve_n_queens(board, 0);
    return 0;
}