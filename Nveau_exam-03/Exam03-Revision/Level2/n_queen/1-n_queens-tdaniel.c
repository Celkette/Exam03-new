#include <stdio.h>       // Pour fprintf
#include <stdlib.h>      // Pour malloc, free, atoi
#include <unistd.h>      // Pour write (bien que non utilisé ici)

int *board;         // Tableau global : board[col] = position ligne de la reine dans colonne col
int board_size;     // Taille globale du plateau (n)

// Affiche la solution actuelle
void print_solution(void)
{
    int i;                          // Variable de boucle
    
    for (i = 0; i < board_size; i++) // Parcourt toutes les colonnes
    {
        fprintf(stdout, "%d", board[i]); // Affiche la position ligne de la reine dans colonne i
        
        if (i < board_size - 1)     // Si ce n'est pas la dernière colonne
            fprintf(stdout, " ");   // Ajoute un espace entre les nombres
    }
    fprintf(stdout, "\n");          // Saut de ligne à la fin
}

// Fonction de remplacement pour abs() car fonction standard non autorisée
int ft_abs(int n)
{
    if (n < 0)          // Si le nombre est négatif
        return (-n);    // Retourne sa valeur positive
    return n;           // Sinon retourne le nombre tel quel
}

// Vérifie si placer une reine à (row, col) est sûr
int is_safe(int row, int col)
{
    // Vérifie toutes les reines déjà placées (colonnes 0 à col-1)
    for (int i = 0; i < col; i++)  // i: itérateur de colonne
    {
        if (board[i] == row)       // Vérifie si les reines sont sur la même ligne
            return 0;              // Position dangereuse
        
        // Vérifie les attaques diagonales
        // Si la différence en lignes égale la différence en colonnes,
        // elles sont sur la même diagonale
        if (ft_abs(board[i] - row) == ft_abs(i - col))
            return 0;              // Position dangereuse
    }
    return 1;                      // Position sûre
}

void solve(int col)                // Fonction récursive de résolution
{
    // Cas de base : si on a placé des reines dans toutes les colonnes
    if (col == board_size)
    {
        print_solution();          // Affiche la solution trouvée
        return ;                   // Retourne pour chercher d'autres solutions
    }
    // Essaie de placer une reine dans chaque ligne de la colonne actuelle
    for (int row = 0; row < board_size; row++)
    {
        // Vérifie si placer une reine à cette position est sûr
        if (is_safe(row, col))
        {
            board[col] = row;      // Place la reine à cette position
            solve(col + 1);        // Résout récursivement pour la colonne suivante
            // Backtrack (retire la reine) - implicite car on écrase
            // board[col] à l'itération suivante ou quand la fonction retourne
        }
    }
}

int main(int ac, char **av)
{
    // Gère le nombre incorrect d'arguments
    if (ac != 2)
    {
        return 0;                  // Sort sans erreur ni affichage
    }
    int n = atoi(av[1]);           // Convertit l'argument en entier
    // Gère les entrées invalides : nombres négatifs, tailles non résolvables
    if (n < 1)
    {
        return 0;                  // Sort sans erreur ni affichage
    }
    board_size = n;                // Définit la variable globale
    board = malloc(sizeof(int) * board_size); // Alloue mémoire pour le plateau
    if (!board)                    // Vérifie si l'allocation a réussi
        return 1;                  // Erreur d'allocation
    solve(0);                      // Commence la résolution depuis la colonne 0
    free(board);                   // Libère la mémoire allouée
    return 0;                      // Succès
}

/********************************************************/
// SANS LES COMMENTAIRES

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int *board;
int board_size;

void print_solution(void)
{
    int i;
    
    for (i = 0; i < board_size; i++)
    {
        fprintf(stdout, "%d", board[i]);
        if (i < board_size - 1)
            fprintf(stdout, " ");
    }
    fprintf(stdout, "\n");
}
int ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return n;
}
int is_safe(int row, int col)
{
	for (int i = 0; i < col; i++)
	{
		if (board[i] == row)
			return 0;
		if (ft_abs(board[i] - row) == ft_abs(i - col))
			return 0;
	}
	return 1;
}

void solve(int col)
{
	if (col == board_size)
	{
		print_solution();
		return ;
	}
	for (int row = 0; row < board_size; row++)
	{
		if (is_safe(row, col))
		{
			board[col] = row;
			solve(col + 1);
		}
	}
}

int main(int ac, char **av)
{
	if (ac != 2)
	{
		return 0;
	}
	int n = atoi(av[1]);
	if (n < 1)
	{
		return 0;
	}
	board_size = n;
	board = malloc(sizeof(int) * board_size);
	if (!board)
		return 1;
	solve(0);
	free(board);
	return 0;
}
