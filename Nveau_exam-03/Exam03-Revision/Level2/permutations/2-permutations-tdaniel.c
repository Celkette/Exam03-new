#include <unistd.h>     // Pour write
#include <stdio.h>      // Pour puts
#include <stdlib.h>     // Pour malloc, calloc, free

int ft_strlen(char *s)  // Calcule la longueur d'une chaîne
{
    int i = 0;          // Initialise le compteur
    while (s[i])        // Parcourt jusqu'au caractère nul
        i++;            // Incrémente le compteur
    return i;           // Retourne la longueur
}

int ft_factorial(int size)  // Calcule la factorielle de size
{
    if (size <= 1)      // Cas de base : 0! = 1! = 1
        return 1;       // Retourne 1
    return (size * ft_factorial(size - 1)); // Appel récursif
}

void	ft_strcpy(char *dest, char *s)  // Copie une chaîne dans une autre
{
    int i;              // Variable de boucle
    for (i = 0; s[i]; i++)  // Parcourt la chaîne source
        dest[i] = s[i]; // Copie chaque caractère
    dest[i] = '\0';     // Ajoute le caractère nul terminal
}

void generate_all_perms(int current_index, int size, char *s, char **all_perms, int *perms_row_index)
{
    if (current_index == size)  // Cas de base : toute la chaîne est permutée
    {
        ft_strcpy(all_perms[(*perms_row_index)], s); // Copie la permutation
        (*perms_row_index)++;   // Incrémente l'index pour la prochaine permutation
        return ;            // Retourne de la récursion
    }
    for (int i = current_index; i < size; i++) // Essaie chaque position
    {
        char temp = s[i];   // Sauvegarde le caractère à l'index i
        s[i] = s[current_index];    // Échange avec le caractère courant
        s[current_index] = temp;    // Complète l'échange
        generate_all_perms(current_index + 1, size, s, all_perms, perms_row_index); // Récursion
        temp = s[i];        // Backtrack : restaure l'état original
        s[i] = s[current_index];    // Premier échange de restauration
        s[current_index] = temp;    // Deuxième échange de restauration
    }
}

int ft_strcmp(char *s1, char *s2)  // Compare deux chaînes
{
    int i = 0;          // Index de parcours
    while (s1[i] && s2[i])  // Tant que les deux chaînes ont des caractères
    {
        if (s1[i] != s2[i]) // Si les caractères diffèrent
            return (s1[i] - s2[i]); // Retourne la différence
        i++;            // Passe au caractère suivant
    }
    return 0;           // Les chaînes sont identiques
}

void sort_perms(char **all_perms, int total_perms)  // Trie les permutations
{
    int i, j;           // Variables de boucle
    for (i = 0; i < total_perms; i++)   // Boucle externe du tri à bulles
    {
        for (j = i + 1; j < total_perms; j++) // Boucle interne
        {
            if (ft_strcmp(all_perms[i], all_perms[j]) > 0) // Si ordre incorrect
            {
                char *tmp = all_perms[i];   // Sauvegarde temporaire
                all_perms[i] = all_perms[j]; // Premier échange
                all_perms[j] = tmp;     // Deuxième échange
            }
        }
    }
}

void	print_perms(char **all_perms, int total_perms) // Affiche toutes les permutations
{
    for (int i = 0; i < total_perms; i++) // Parcourt toutes les permutations
        puts(all_perms[i]); // Affiche chaque permutation
}

void free_all_perms(char **all_perms, int total_perms) // Libère toute la mémoire
{
    if (all_perms)      // Vérifie que le pointeur n'est pas NULL
    {
        for (int i = 0; i < total_perms; i++) // Parcourt chaque permutation
        {
            if (all_perms[i])   // Vérifie que la permutation existe
                free(all_perms[i]); // Libère la chaîne
        }
        free(all_perms);    // Libère le tableau de pointeurs
    }
}

int main(int ac, char **av) // Fonction principale
{
    if (ac != 2)        // Vérifie le nombre d'arguments
    {
        return 0;       // Sort sans affichage si mauvais nombre
    }
    char *s = av[1];    // Récupère la chaîne d'entrée
    int size = ft_strlen(s); // Calcule la taille de la chaîne
    if (size == 0)      // Vérifie si la chaîne est vide
    {
        return 0;       // Sort sans affichage si chaîne vide
    }
    int total_perms = ft_factorial(size); // Calcule le nombre total de permutations
    char **all_perms = malloc(sizeof(char *) * total_perms); // Alloue le tableau de pointeurs
    if (!all_perms)     // Vérifie l'allocation
        return 1;       // Erreur d'allocation
    for (int i = 0; i < total_perms; i++) // Alloue chaque chaîne de permutation
    {
        all_perms[i] = calloc(size + 1, sizeof(char)); // Alloue et initialise à zéro
        if (!all_perms[i])  // Vérifie l'allocation
        {
            free_all_perms(all_perms, i); // Libère ce qui a été alloué
            return 1;   // Erreur d'allocation
        }
    }
    int perms_row_index = 0; // Index pour stocker les permutations
    int current_index = 0;   // Index de départ pour la génération
    generate_all_perms(current_index, size, s, all_perms, &perms_row_index); // Génère toutes les permutations
    sort_perms(all_perms, total_perms); // Trie les permutations
    print_perms(all_perms, total_perms); // Affiche les permutations
    free_all_perms(all_perms, total_perms); // Libère toute la mémoire
    return 0;           // Succès
}

/*************************************************************/
//SANS COMMENTAIRE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int ft_strlen(char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return i;
}

int ft_factorial(int size)
{
    if (size <= 1)
        return 1;
    return (size * ft_factorial(size - 1));
}

void	ft_strcpy(char *dest, char *s)
{
    int i;
    for (i = 0; s[i]; i++)
        dest[i] = s[i];
    dest[i] = '\0';
}

void generate_all_perms(int current_index, int size, char *s, char **all_perms, int *perms_row_index)
{
    if (current_index == size)
    {
        ft_strcpy(all_perms[(*perms_row_index)], s);
        (*perms_row_index)++;
        return ;
    }
    for (int i = current_index; i < size; i++)
    {
        char temp = s[i];
        s[i] = s[current_index];
        s[current_index] = temp;
        generate_all_perms(current_index + 1, size, s, all_perms, perms_row_index);
        temp = s[i];
        s[i] = s[current_index];
        s[current_index] = temp;
    }
}

int ft_strcmp(char *s1, char *s2)
{
    int i = 0;
    while (s1[i] && s2[i])
    {
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
        i++;
    }
    return 0;
}

void sort_perms(char **all_perms, int total_perms)
{
    int i, j;
    for (i = 0; i < total_perms; i++)
    {
        for (j = i + 1; j < total_perms; j++)
        {
            if (ft_strcmp(all_perms[i], all_perms[j]) > 0)
            {
                char *tmp = all_perms[i];
                all_perms[i] = all_perms[j];
                all_perms[j] = tmp;
            }
        }
    }
}

void	print_perms(char **all_perms, int total_perms)
{
    for (int i = 0; i < total_perms; i++)
        puts(all_perms[i]);
}

void free_all_perms(char **all_perms, int total_perms)
{
    if (all_perms)
    {
        for (int i = 0; i < total_perms; i++)
        {
            if (all_perms[i])
                free(all_perms[i]);
        }
        free(all_perms);
    }
}

int main(int ac, char **av)
{
    if (ac != 2)
        return 0;
    char *s = av[1];
    int size = ft_strlen(s);
    if (size == 0)
        return 0;
    int total_perms = ft_factorial(size);
    char **all_perms = malloc(sizeof(char *) * total_perms);
    if (!all_perms)
        return 1;
    for (int i = 0; i < total_perms; i++)
    {
        all_perms[i] = calloc(size + 1, sizeof(char));
        if (!all_perms[i])
        {
            free_all_perms(all_perms, i);
            return 1;
        }
    }
    int perms_row_index = 0;
    int current_index = 0;
    generate_all_perms(current_index, size, s, all_perms, &perms_row_index);
    sort_perms(all_perms, total_perms);
    print_perms(all_perms, total_perms);
    free_all_perms(all_perms, total_perms);
    return 0;
}

/***********************************************************/
//COMMENTAIRE ORIGINAUX
//correction free malloc faite


// TO DO: NEEDS TO HANDLE MALLOC FAILURES AND FREE MEMORY
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/* basic logic of the program: 
- use factorial function to calculate how many permutations there are 
for a given number of unique characters (i.e. the size of the given string)
- use malloc to create a matrix (char **all_perms) to hold all permutations.
- the number of rows in the matrix equals the total number of permutations possible,
and the number of columns in each row equals the size of the original string given, plus nul-terminator.
- use recursion to generate permutations and copy them into the matrix one at a time.
- sort the permutations in the matrix using strcmp function and bubble sort algorithm.
- print out the sorted matrix.
*/


int ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return i;
}

// calculate the total number of permutations possible
int ft_factorial(int size)
{
	if (size <= 1)
		return 1;
	return (size * ft_factorial(size - 1));
}

void	ft_strcpy(char *dest, char *s)
{
	int i;
	for (i = 0; s[i]; i++)
		dest[i] = s[i];
	dest[i] = '\0';
}

// recursive function to generate all permutations and store them in the matrix
void generate_all_perms(int current_index, int size, char *s, char **all_perms, int *perms_row_index)
{
	// base case: reaching end of the string
	if (current_index == size)
	{
		ft_strcpy(all_perms[(*perms_row_index)], s);
		(*perms_row_index)++; // Increment the index for the next permutation
		return ;
	}
	/* Start from the given current index in the string: 
	1) keep the character at the current index in its current position,
	which is implicit in the below loop logic 
	when the iterator i is equal to the current index (swapping 
	the character with itself -> nothing happens); OR 
	2) swap the character at the current index with each character to the right
	of itself (when iterator i is larger than the current index and smaller than size)
	If the current index is equal to size, print the permutation, else 
	keep operating similarly for all valid index positions. 
	Thereafter, swap back the values to original values to initiate backtracking.*/
	for (int i = current_index; i < size; i++)
	{
		char temp = s[i]; 
		s[i] = s[current_index];
		s[current_index] = temp;
		// recursive call to move to the next index position
		generate_all_perms(current_index + 1, size, s, all_perms, perms_row_index);
		// backtracking: swap the charaters again
		temp = s[i]; 
		s[i] = s[current_index];
		s[current_index] = temp;
	}
}

// simplified strcmp function that compares two strings with equal lengths
int ft_strcmp(char *s1, char *s2)
{
	int i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return 0;
}

// sorting permutations in the matrix based on alphabetic order
void sort_perms(char **all_perms, int total_perms)
{
	int i, j;
	for (i = 0; i < total_perms; i++)
	{
		for (j = i + 1; j < total_perms; j++)
		{
			if (ft_strcmp(all_perms[i], all_perms[j]) > 0)
			{
				char *tmp = all_perms[i];
				all_perms[i] = all_perms[j];
				all_perms[j] = tmp;
			}
		}
	}
}

void	print_perms(char **all_perms, int total_perms)
{
	for (int i = 0; i < total_perms; i++)
		puts(all_perms[i]);
}
// Fonction pour libérer la mémoire allouée
void free_all_perms(char **all_perms, int total_perms)
{
    if (all_perms)
    {
        for (int i = 0; i < total_perms; i++)
        {
            if (all_perms[i])
                free(all_perms[i]);
        }
        free(all_perms);
    }
}
int main(int ac, char **av)
{
	if (ac != 2)
	{
		return 0;
	}
	char *s = av[1];
	int size = ft_strlen(s); // number of unique (alphabetic) characters in the string 
	if (size == 0) 
	{
		return 0;
    }
	// Calculate the total number of permutations 
	int total_perms = ft_factorial(size);

	// Allocate memory for an array of char pointers.
    // Each pointer will point to a dynamically allocated string representing a permutation.
	char **all_perms = malloc(sizeof(char *) * total_perms);
	if (!all_perms)  // CORRECTION : Vérification malloc
        return 1;
	// Allocate memory for each individual permutation string.
    // Each string needs 'size + 1' bytes (for characters + null terminator)
	for (int i = 0; i < total_perms; i++)
	{
		all_perms[i] = calloc(size + 1, sizeof(char));
		if (!all_perms[i])  // CORRECTION : Vérification calloc
		{	// Libère ce qui a déjà été alloué
			free_all_perms(all_perms, i);
			return 1;
		}
	}
	int perms_row_index = 0;
	int current_index = 0;
	generate_all_perms(current_index, size, s, all_perms, &perms_row_index);
	sort_perms(all_perms, total_perms);
	print_perms(all_perms, total_perms);
	// CORRECTION : Libération de toute la mémoire allouée
    free_all_perms(all_perms, total_perms);
	return 0;
}
