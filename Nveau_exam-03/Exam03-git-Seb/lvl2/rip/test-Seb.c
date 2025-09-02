#include <unistd.h>
#include <stdlib.h>

// Helper to print a solution with spaces for removed chars
void print_solution(const char *src, int len, const char *mask) {
    for (int i = 0; i < len; i++) {
        if (mask[i])
            write(1, " ", 1);
        else
            write(1, &src[i], 1);
    }
    write(1, "\n", 1);
}

int min_removals(const char *str, int len) {
    int open = 0, close = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] == '(')
            open++;
        else if (str[i] == ')')
            (open > 0) ? open-- : close++;
    }
    return open + close;
}

// Recursively generate all solutions
void solve(const char *str, int len, char *mask, int idx, int open, int close, int rem_open, int rem_close, int *found) {
    if (idx == len) {
        if (rem_open == 0 && rem_close == 0 && open == 0) {
            print_solution(str, len, mask);
            *found = 1;
        }
        return;
    }
    if (str[idx] == '(') {
        // Remove current '(' if allowed
        if (rem_open > 0) {
            mask[idx] = 1;
            solve(str, len, mask, idx + 1, open, close, rem_open - 1, rem_close, found);
            mask[idx] = 0;
        }
        // Keep current '('
        solve(str, len, mask, idx + 1, open + 1, close, rem_open, rem_close, found);
    } else if (str[idx] == ')') {
        // Remove current ')' if allowed
        if (rem_close > 0) {
            mask[idx] = 1;
            solve(str, len, mask, idx + 1, open, close, rem_open, rem_close - 1, found);
            mask[idx] = 0;
        }
        // Keep current ')', only if it matches an open '('
        if (open > 0)
            solve(str, len, mask, idx + 1, open - 1, close, rem_open, rem_close, found);
    } else {
        // Should not happen - input only has '(' and ')'
        solve(str, len, mask, idx + 1, open, close, rem_open, rem_close, found);
    }
}

// Entry point
int main(int ac, char **av) {
    if (ac != 2)
        return (write(2, "Usage: ./rip \"parentheses\"\n", 27), 1);

    char *str = av[1];
    int len = 0;
    while (str[len])
        len++;
    int open = 0, close = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] == '(')
            open++;
        else if (str[i] == ')')
            (open > 0) ? open-- : close++;
    }
    int rem_open = open, rem_close = close;
    char *mask = malloc(len);
    if (!mask)
        return 1;
    for (int i = 0; i < len; i++)
        mask[i] = 0;
    int found = 0;
    solve(str, len, mask, 0, 0, 0, rem_open, rem_close, &found);
    free(mask);
    return 0;
}
