#include "power_set.h"

// Variables globales pour stocker les données du problème
static int	target;    // La somme cible à atteindre
static int	*array_nb;      // Tableau des nombres à utiliser
static int	n;         // Nombre de valeurs dans le tableau array_nb
static int	*sub_array;      // Tableau temporaire pour stocker le sous-ensemble courant
static int	sub_size;  // Taille actuelle du sous-ensemble
static int	found;	   // flag si une sol a été trouvé

// Fonction de backtracking pour explorer tous les sous-ensembles
void	bt(int start, int sum)
{
    if (sum == target && sub_size > 0) // Si la somme courante == cible et sous-ensemble n'est pas vide
    {
        found = 1;                     // Marque qu'une solution a été trouvée
        printf("%d", sub_array[0]);          // Affiche le premier élément du sous-ensemble
        for (int i = 1; i < sub_size; i++) // Affiche les autres éléments séparés par un espace
            printf(" %d", sub_array[i]);
        printf("\n");                  // Passe à la ligne suivante
    }
    for (int i = start; i < n; i++) // Parcourt les éléments à partir de 'start'
    {
        sub_array[sub_size++] = array_nb[i];      // Ajoute array_nb[i] au sous-ensemble courant
        bt(i + 1, sum + array_nb[i]);       // Appelle récursivement en avançant dans le tableau et en ajoutant array_nb[i] à la somme
        sub_size--;                    // Retire array_nb[i] du sous-ensemble (backtrack)
    }
}

int	main(int ac, char **av)
{
    if (ac < 2)           // Vérifie qu'il y a au moins un argument (la cible)
        return (0);        // Si non, quitte le programme

    target = atoi(av[1]); // Récupère la somme cible depuis le premier argument
    n = ac - 2;           // Calcule le nombre de valeurs à traiter (tous les arguments sauf le nom du programme et la cible)

    array_nb = malloc(sizeof(int) * n); // Alloue le tableau des nombres
    if (!array_nb)                      // Vérifie l'allocation
        return (1);                // Quitte avec code d'erreur si échec

    sub_array = malloc(sizeof(int) * n); // Alloue le tableau temporaire pour les sous-ensembles
    if (!sub_array)                      // Vérifie l'allocation
        return (1);                // Quitte avec code d'erreur si échec

    for (int i = 0; i < n; i++)    // Remplit le tableau array_nb avec les arguments
        array_nb[i] = atoi(av[i + 2]);

    sub_size = 0;                  // Initialise la taille du sous-ensemble à 0
    bt(0, 0);                      // Lance le backtracking à partir du début du tableau et somme 0

	if (!found)                      // Si aucune solution n'a été trouvée
        printf("\n");                // Affiche une ligne vide
	
    free(array_nb);                     // Libère la mémoire allouée pour array_nb
    free(sub_array);                     // Libère la mémoire allouée pour sub
    return (0);                    // Quitte le programme avec succès
}
/**************************************/
/*#include "power_set.h"

static int	target;
static int	*array_nb;
static int	n;
static int	*sub_array;
static int	sub_size;
static int	found;

void	bt(int start, int sum)
{
	if (sum == target && sub_size > 0)
	{
		found = 1;
		printf("%d", sub_array[0]);
		for (int i = 1; i < sub_size; i++)
			printf(" %d", sub_array[i]);
		printf("\n");
		
	}
	for (int i = start; i < n; i++)
	{
		sub_array[sub_size++] = array_nb[i];
		bt(i + 1, sum + array_nb[i]);
		sub_size--;
	}
}
int	main(int ac, char **av)
{
	if (ac < 2)
		return (0);
	target = atoi(av[1]);
	n = ac - 2;
	array_nb = malloc(sizeof(int) * n);
	if (!array_nb)
		//exit(1);//pas standard
		return (1);
	sub_array = malloc(sizeof(int) * n);
	if (!sub_array)
		exit(1);
	for (int i = 0; i < n; i++)
		array_nb[i] = atoi(av[i + 2]);
	sub_size = 0;
	bt(0, 0);
	if (!found)
        printf("\n");
	free(array_nb);
	free(sub_array);
	return (0);
}
*/
/*************************************/
/**** DEROULE******/
/* pour  ./powerset 3 1 0 2 3
while (i < n)
	{
		sub_array[sub_size] = array_nb[i]; // Ajoute l'élément à la position sub_size
		sub_size++;                        // Incrémente sub_size après l'ajout
		bt(i + 1, sum + array_nb[i]);
		sub_size--;                        // Décrémente sub_size après le backtrack
		i++;
	}

Voici le déroulé précis pour /powerset t a b c d (avec target = t, array_nb = [a, b, c, d]) :

Premier appel : bt(0, 0)
i = 0 → ajoute a (sub[0] = a, sub_size = 1)
Appel récursif : bt(1, a)
i = 1 → ajoute b (sub[1] = b, sub_size = 2)
Appel récursif : bt(2, a + b)
i = 2 → ajoute c (sub[2] = c, sub_size = 3)
Appel récursif : bt(3, a + b + c)
Si a + b + c == t, on affiche a b c
sub_size-- (retire c)
i = 3 → ajoute d (sub[2] = d, sub_size = 3)
Appel récursif : bt(4, a + b + d)
Si a + b + d == t, on affiche a b d
sub_size-- (retire d)
sub_size-- (retire b)
i = 2 → ajoute c (sub[1] = c, sub_size = 2)
Appel récursif : bt(3, a + c)
Si a + c == t, on affiche a c
sub_size-- (retire c)
i = 3 → ajoute d (sub[1] = d, sub_size = 2)
Appel récursif : bt(4, a + d)
Si a + d == t, on affiche a d
sub_size-- (retire d)
sub_size-- (retire a)
i = 1 → ajoute b (sub[0] = b, sub_size = 1)
Appel récursif : bt(2, b)
i = 2 → ajoute c (sub[1] = c, sub_size = 2)
Appel récursif : bt(3, b + c)
Si b + c == t, on affiche b c
sub_size-- (retire c)
i = 3 → ajoute d (sub[1] = d, sub_size = 2)
Appel récursif : bt(4, b + d)
Si b + d == t, on affiche b d
sub_size-- (retire d)
sub_size-- (retire b)
i = 2 → ajoute c (sub[0] = c, sub_size = 1)
Appel récursif : bt(3, c)
i = 3 → ajoute d (sub[1] = d, sub_size = 2)
Appel récursif : bt(4, c + d)
Si c + d == t, on affiche c d
sub_size-- (retire d)
sub_size-- (retire c)
i = 3 → ajoute d (sub[0] = d, sub_size = 1)
Appel récursif : bt(4, d)
Si d == t, on affiche d
sub_size-- (retire d)
À chaque fois que la somme du sous-ensemble courant atteint la cible, on affiche la solution.
On retire ensuite le dernier élément (sub_size--) pour explorer les autres possibilités.