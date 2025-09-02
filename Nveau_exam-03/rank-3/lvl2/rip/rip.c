#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>

int ft_strlen(const char *s) {
    int len = 0;
    while (s[len])
        len++;
    return len;
}

void dfs(char *s, int index, int left, int right, int open, char *buffer, int buf_idx, int len) {
    if (s[index] == '\0') {
        if (open == 0) {
            buffer[buf_idx] = '\0';
            puts(buffer);
        }
        return;
    }
    
    char c = s[index];
    if (c == '(' && left > 0) {
        buffer[buf_idx] = ' ';
        dfs(s, index + 1, left - 1, right, open, buffer, buf_idx + 1, len);
    }
    if (c == ')' && right > 0) {
        buffer[buf_idx] = ' ';
        dfs(s, index + 1, left, right - 1, open, buffer, buf_idx + 1, len);
    }
    
    buffer[buf_idx] = c;
    if (c == '(')
        dfs(s, index + 1, left, right, open + 1, buffer, buf_idx + 1, len);
    else if (c == ')' && open > 0)
        dfs(s, index + 1, left, right, open - 1, buffer, buf_idx + 1, len);
    else if (c != '(' && c != ')')
        dfs(s, index + 1, left, right, open, buffer, buf_idx + 1, len);
}

void min_remove_to_balance(char *s) {
    int left = 0, right = 0;
    int len = ft_strlen(s);
    char buffer[len + 1];
    
    for (int i = 0; i < len; i++) {
        if (s[i] == '(')
            left++;
        else if (s[i] == ')') {
            if (left > 0) left--;
            else right++;
        }
    }
    dfs(s, 0, left, right, 0, buffer, 0, len);
}

int main(int argc, char **argv) {
    if (argc == 2)
        min_remove_to_balance(argv[1]);
    return 0;
}