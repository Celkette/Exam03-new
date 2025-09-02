#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* calcule k! récursivement */
static int  factorial(int k)
{
    if (k <= 1)
        return 1;
    return k * factorial(k - 1);
}

/* compare pour qsort */
static int  cmpfunc(const void *a, const void *b)
{
    return strcmp(*(char **)a, *(char **)b);
}

/* teste si c existe dans s[0..idx] */
static int  exists(char const *s, char c, int idx)
{
    if (idx < 0)
        return 0;
    if (s[idx] == c)
        return 1;
    return exists(s, c, idx - 1);
}

/*
** génère toutes les permutations de 'remain' préfixées par 'prefix'
** et les stocke dans perms[*count], incrémente *count.
*/
static void permute_rec(char const *prefix,
                       char const *remain,
                       char **perms,
                       int *count,
                       int index)
{
    int len = strlen(remain);
    if (index == len)
        return;
    /* saute les doublons */
    if (!exists(remain, remain[index], index - 1))
    {
        /* nouveau préfixe = prefix + remain[index] */
        int lp = strlen(prefix);
        char *new_pref = malloc(lp + 2);
        if (!new_pref)
            exit(1);
        if (lp > 0)
            strncpy(new_pref, prefix, lp);
        new_pref[lp] = remain[index];
        new_pref[lp + 1] = '\0';

        /* nouveau remain sans le caractère à index */
        char *new_rem = malloc(len);
        if (!new_rem)
            exit(1);
        /* copie avant index */
        if (index > 0)
            strncpy(new_rem, remain, index);
        /* copie après index */
        if (index < len - 1)
            strncpy(new_rem + index,
                    remain + index + 1,
                    len - index - 1);
        new_rem[len - 1] = '\0';

        /* si fin, on a une permutation complète */
        if (len - 1 == 0)
            perms[(*count)++] = strdup(new_pref);
        else
            permute_rec(new_pref, new_rem, perms, count, 0);

        free(new_pref);
        free(new_rem);
    }
    /* passe à l’index suivant */
    permute_rec(prefix, remain, perms, count, index + 1);
}

static void permute(char const *prefix,
                    char const *remain,
                    char **perms,
                    int *count)
{
    if (strlen(remain) == 0)
        return;
    permute_rec(prefix, remain, perms, count, 0);
}

/*
** affiche perms[] en (n-1)! lignes × n colonnes
** idx = début de la ligne courante
*/
static void print_cols(char **perms, int n, int idx, int col)
{
    if (col >= n)
        return;
    printf("%s", perms[idx + col]);
    if (col < n - 1)
        printf(" ");
    print_cols(perms, n, idx, col + 1);
}

static void print_rows(char **perms, int total, int n, int idx)
{
    if (idx >= total)
        return;
    print_cols(perms, n, idx, 0);
    printf("\n");
    print_rows(perms, total, n, idx + n);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("\n");
        return 0;
    }
    char *input = argv[1];
    int n = strlen(input);
    int total = factorial(n);
    /* alloue le tableau de permutations */
    char **perms = malloc(sizeof(char *) * total);
    if (!perms)
        exit(1);
    int count = 0;
    /* génération */
    permute("", input, perms, &count);
    /* tri lexicographique */
    qsort(perms, count, sizeof(char *), cmpfunc);
    /* affichage en colonnes verticales */
    print_rows(perms, count, n, 0);
    /* libération */
    for (int i = 0; i < count; i++)
        free(perms[i]);
    free(perms);
    return 0;
}