#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

size_t ft_strlen(const char *s) {
    size_t len = 0;
    while (s[len])
        len++;
    return len;
}

void sort_string(char *str) {
    size_t i, j, len = ft_strlen(str);
    i = 0;
    while (i < len - 1)
    {
        j = i + 1;
        while (j < len)
        {
            if (str[i] > str[j])
                swap(&str[i], &str[j]);
            j++;
        }
        i++;
    }
}

int next_permutation(char *str, int len) {
    int i = len - 2;
    while (i >= 0 && str[i] >= str[i + 1])
        i--;
    printf("%d\n", i);
    if (i < 0)
        return 0;
    int j = len - 1;
    while (str[j] <= str[i])
        j--;
    printf("%d\n", j);
    swap(&str[i], &str[j]);
    j = len - 1;
    i++;
    while (i < j)
    {
        swap(&str[i], &str[j]);
        i++;
        j--;
    }
    return 1;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        write(1, "Usage: ./a.out string\n", 22);
        return 1;
    }
    size_t len = ft_strlen(argv[1]);
    char *str = (char *)malloc(len + 1);
    if (!str)
        return 1;
    size_t i = 0;
    while (i < len)
    {
        str[i] = argv[1][i];
        i++;
    }
    str[len] = '\0';
    sort_string(str);
    puts(str); // Affichage initial avant la boucle
    while (next_permutation(str, len)) {
        puts(str);
    }
    
    free(str);
    return 0;
}
