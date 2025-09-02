#include <stdio.h>      // Pour printf()
#include <string.h>     // Pour strlen() 
#include <stdlib.h>     // Pour malloc(), free(), realloc()
#include <unistd.h>     // Pour read(), STDIN_FILENO

// Custom implementation of strncmp
int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i;           // Index pour parcourir les chaînes
    i = 0;              // Initialisation à 0
    if (n == 0)         // Si on compare 0 caractères
        return (0);     // Les chaînes sont égales
    while (i < n && s1[i] == s2[i] && s1[i])  // Compare tant que : pas fini, égaux, pas '\0'
        i++;            // Passe au caractère suivant
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);  // Retourne la différence
}
// Custom implementation of strdup
char *ft_strdup(const char *s) 
{
    size_t len = strlen(s);     // Calcule la longueur de la chaîne source
    char *dup = malloc(len + 1); // Alloue la mémoire (+1 pour '\0')
    if (!dup)                   // Si l'allocation échoue
        return NULL;            // Retourne NULL
    for (size_t i = 0; i <= len; ++i)  // Copie tous les caractères + '\0'
        dup[i] = s[i];          // Copie caractère par caractère
    return dup;                 // Retourne la copie
}
// Custom implementation of memset
void *ft_memset(void *ptr, int value, size_t num) 
{
    unsigned char *p = ptr;     // Cast en unsigned char* pour manipulation octet par octet
    for (size_t i = 0; i < num; ++i)  // Pour chaque octet à remplir
        p[i] = (unsigned char)value;  // Met la valeur dans l'octet
    return ptr;                 // Retourne le pointeur original
}

char *read_line(void) 
{
    char c, *line = NULL;       // Caractère lu et pointeur vers la ligne
    size_t len = 0;             // Longueur courante de la ligne
    while (read(STDIN_FILENO, &c, 1) > 0) {  // Lit caractère par caractère depuis stdin
        char *tmp = realloc(line, len + 2);   // Réalloue +2 (nouveau char + '\0')
        if (!tmp) {             // Si la réallocation échoue
            free(line);         // Libère la mémoire déjà allouée
            return NULL;        // Retourne NULL
        }
        line = tmp;             // Met à jour le pointeur
        line[len++] = c;        // Stocke le caractère et incrémente len
        line[len] = 0;          // Termine la chaîne par '\0'
    }
    return line;                // Retourne la ligne complète
}
// Fonction de filtrage
char *filter(const char *s, const char *tf)
{
    size_t slen = strlen(s);    // Longueur de la chaîne source
    size_t tlen = tf ? strlen(tf) : 0;  // Longueur du pattern (0 si tf est NULL)
    size_t i = 0;               // Index dans la chaîne source
    size_t k = 0;               // Index dans la chaîne destination
    
    if (!s || !tf || !tlen)     // Si s ou tf est NULL ou tf est vide
        return ft_strdup(s ? s : "");  // Retourne une copie de s (ou chaîne vide)
    
    char *d = malloc(slen + 1); // Alloue la mémoire pour le résultat
    if (!d)                     // Si l'allocation échoue
        return NULL;            // Retourne NULL
    
    while (s[i])                // Parcourt toute la chaîne source
    {
        if (!ft_strncmp(s + i, tf, tlen))  // Si on trouve le pattern à la position i
        {
            ft_memset(d + k, '*', tlen);   // Remplit avec des '*' (autant que le pattern)
            k += tlen;          // Avance k de la longueur du pattern
            i += tlen;          // Avance i de la longueur du pattern
        }
        else                    // Si pas de correspondance
            d[k++] = s[i++];    // Copie le caractère et avance les deux index
    }
    d[k] = 0;                   // Termine la chaîne résultat par '\0'
    return d;                   // Retourne la chaîne filtrée
}

int main(int ac, char **av)
{
    if (ac != 2 || !av[1] || !av[1][0])       // Vérification arguments
        return 1;
    char *in = read_line();
    if (!in)
	    return 1;
    char *out = filter(in, av[1]);
    if (!out)
    {
	    free(in);
	    return 1;
    }
    printf("%s", out);
    free(out); free(in);
    return 0;
}

/************************************************************/
//SANS COMMENTAIRES

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// Custom implementation of strncmp
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && s1[i] == s2[i] && s1[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
// Custom implementation of strdup
char *ft_strdup(const char *s) {
    size_t len = strlen(s);
    char *dup = malloc(len + 1);
    if (!dup)
	    return NULL;
    for (size_t i = 0; i <= len; ++i)
        dup[i] = s[i];
    return dup;
}
// Custom implementation of memset
void *ft_memset(void *ptr, int value, size_t num) {
    unsigned char *p = ptr;
    for (size_t i = 0; i < num; ++i)
        p[i] = (unsigned char)value;
    return ptr;
}

char *read_line(void) {
    char c, *line = NULL;
    size_t len = 0;
    while (read(STDIN_FILENO, &c, 1) > 0) {
        char *tmp = realloc(line, len + 2);
        if (!tmp) { free(line); return NULL; }
        line = tmp;
        line[len++] = c;
        line[len] = 0;
    }
    return line;
}

char *filter(const char *s, const char *tf)
{
	size_t	slen = strlen(s);
	size_t	tlen = tf ? strlen(tf) : 0;
	size_t	i = 0;
	size_t	k = 0;
    if (!s || !tf || !tlen)
	    return ft_strdup(s ? s : "");
    char *d = malloc(slen + 1);
    if (!d)
	    return NULL;
    while (s[i])
    {
        if (!ft_strncmp(s + i, tf, tlen))
	{
            ft_memset(d + k, '*', tlen);
            k += tlen; i += tlen;
        }
	else
	       d[k++] = s[i++];
    }
    d[k] = 0;
    return d;
}

int main(int ac, char **av)
{
    if (ac != 2 || !av[1] || !av[1][0])       // Vérification arguments
        return 1;
    char *in = read_line();
    if (!in)
	    return 1;
    char *out = filter(in, av[1]);
    if (!out)
    {
	    free(in);
	    return 1;
    }
    printf("%s", out);
    free(out); free(in);
    return 0;
}
