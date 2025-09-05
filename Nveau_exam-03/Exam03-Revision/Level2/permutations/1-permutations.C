
//algorithme "next_permutation" (aussi appelé algorithme de Narayana Pandita)

#include <stdio.h>      // Pour puts
#include <stdlib.h>     // Pour malloc, free
#include <string.h>     // Pour strlen

// Duplique une chaîne de caractères (alloue et copie chaque caractère)
char *ft_strdup(char *s)
{
    int len = 0;
    while (s[len])
        len++;
    char *dup = malloc(sizeof(char) * (len + 1));
    if (!dup)  
        return NULL;
    for (int i = 0; i <= len; i++)
        dup[i] = s[i];
    return dup;
}

// Calcule la longueur d'une chaîne (nombre de caractères avant le '\0')
int ft_strlen(char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return i;
}
// Échange deux caractères pointés par a et b
void swap(char *a, char *b) {
    char tmp = *a;
    *a = *b;
    *b = tmp;
}
// Inverse une sous-chaîne de s entre les indices start et end inclus
// Exemple : s = "abcd", reverse(s, 1, 3) => "adcb"
void reverse(char *s, int start, int end) {
    // Tant que start < end, échange les caractères aux extrémités et rapproche les indices
    while (start < end) {
        swap(&s[start], &s[end]); // Échange s[start] et s[end]
        start++;                  // Avance start
        end--;                    // Recule end
    }
}
// Trie la chaîne s en ordre croissant (tri à bulles)
void ft_sort(char *s)
{
    for(int x = 0; s[x]; x++)
    {
        for(int y = x + 1; s[y]; y++)
        {
            if(s[x] > s[y])
                swap(&s[x], &s[y]);
        }
    }
}
// Génère la permutation lexicographique suivante de s
// Retourne 1 si une nouvelle permutation existe, 0 sinon (fin)
int next_permutation(char *s, int n) {
    int i = n - 2;
    // Cherche le plus grand i tel que s[i] < s[i+1]
    while (i >= 0 && s[i] >= s[i + 1])
        i--;
    if (i < 0)         // Si aucune permutation suivante, on a fini
        return 0;
    int j = n - 1;
    // Cherche le plus grand j > i tel que s[j] > s[i]
    while (s[j] <= s[i])
        j--;
    swap(&s[i], &s[j]);        // Échange s[i] et s[j]
    reverse(s, i + 1, n - 1);  // Inverse la sous-chaîne après i pour obtenir la plus petite permutation suivante
    return 1;
}

int main(int ac, char **av) {
    if (ac != 2)           // Vérifie qu'il y a exactement un argument
        return 1;
    int n = ft_strlen(av[1]);      // Calcule la longueur de la chaîne
    char *s = ft_strdup(av[1]);    // Duplique la chaîne pour la manipuler
    if (!s)                       // Vérifie l'allocation
        return 1;
    ft_sort(s);                   // Trie la chaîne pour commencer par la plus petite permutation
	puts(s); // Affiche la première permutation
    while (next_permutation(s, n)) 
        puts(s); // Affiche la permutation suivante
    free(s);                      // Libère la mémoire allouée
    return 0;                     // Fin du programme
}
/*******************************************************/
//SANS COMMENTAIRES
/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*ft_strdup(char *s)
{
    int len = 0;
    while (s[len])
        len++;
    char *dup = malloc(sizeof(char) * (len + 1));
    if (!dup)
        return NULL;
    for (int i = 0; i <= len; i++)
        dup[i] = s[i];
    return (dup);
}
int ft_strlen(char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return i;
}
void	ft_sort(char *s)
{
	for(int x = 0; s[x]; x++)
	{
		for(int y = x + 1; s[y]; y++)
		{
			if(s[x] > s[y])
				ft_swap(&s[x], &s[y]);
		}
	}
}
// Fonction pour échanger deux caractères
void swap(char *a, char *b) {
    char tmp = *a;
    *a = *b;
    *b = tmp;
}

// Fonction pour inverser une sous-chaîne
void reverse(char *s, int start, int end) {
    while (start < end) {
        swap(&s[start], &s[end]);
        start++;
        end--;
    }
}

// Génère la permutation lexicographique suivante, retourne 1 si possible, 0 sinon
int next_permutation(char *s, int n) {
    int i = n - 2;
    while (i >= 0 && s[i] >= s[i + 1])
        i--;
    if (i < 0)
        return 0;
    int j = n - 1;
    while (s[j] <= s[i])
        j--;
    swap(&s[i], &s[j]);
    reverse(s, i + 1, n - 1);
    return 1;
}

int main(int ac, char **av) {
    if (ac != 2)
        return 1;
    int n = ft_strlen(av[1]);
    char *s = ft_strdup(av[1]);
    if (!s)
        return 1;

    // Tri initial pour commencer par la plus petite permutation
    ft_sort(s);

    do {
        puts(s);
    } while (next_permutation(s, n));

    free(s);
    return 0;
}*/