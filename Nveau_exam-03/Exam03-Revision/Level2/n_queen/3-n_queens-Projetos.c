#include <stdio.h>      // Pour fprintf
#include <stdlib.h>     // Pour atoi, malloc, free

void	print(int *board, int n)
{
    for(int x = 0; x < n; x++)         // Parcourt chaque colonne
    {
        fprintf(stdout, "%d", board[x]); // Affiche la position de la reine dans la colonne x
        if(x < n - 1)                    // Si ce n'est pas la dernière colonne
            fprintf(stdout, " ");         // Ajoute un espace
    }
    fprintf(stdout, "\n");               // Saut de ligne final
}

int	check(int *board, int col, int row)
{
    for(int x = 0; x < col; x++)        // Parcourt les colonnes déjà remplies
    {
        // Vérifie même ligne ou même diagonale
        if(board[x] == row || board[x] - row == col - x || row - board[x] == col - x)
            return 1;                   // Position non sûre
    }
    return 0;                           // Position sûre
}

void	solve(int *board, int col, int n)
{
    if(col == n)                        // Cas de base : toutes les colonnes sont remplies
    {
        print(board, n);                // Affiche la solution trouvée
        return ;
    }
    for(int row = 0; row < n; row++)    // Essaie chaque ligne pour la colonne courante
    {
        if(check(board, col, row) == 0) // Si la position est sûre
        {
            board[col] = row;           // Place la reine
            solve(board, col + 1, n);   // Récursion pour la colonne suivante
        }
    }
}

int main(int ac, char **av)
{
    if (ac != 2)                        // Vérifie le nombre d'arguments
        return (1);                     // Erreur si mauvais nombre d'arguments
    int n = atoi(av[1]);                // Convertit l'argument en entier
    int *board = malloc(sizeof(int) * n); // Alloue le tableau des positions
    if (!board)                         // Vérifie l'allocation mémoire
        return (1);                     // Erreur allocation
    solve(board, 0, n);                 // Lance la résolution
    free(board);                        // Libère la mémoire
    return (0);                         // Succès
}

/********************************************************/
// SANS LES COMMENTAIRES

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


void	print(int *board, int n)
{
	for(int x = 0; x < n; x++)
	{
		fprintf(stdout, "%d", board[x]);
		if(x < n - 1)
			fprintf(stdout, " ");
		else
			fprintf(stdout, "\n");
	}
}


int	check(int *board, int col, int row)
{
	for(int x = 0; x < col; x++)
	{
		if(board[x] == row || board[x] - row == col - x || row - board[x] == col - x)
			return 1;
	}
	return 0;
}

void	solve(int *board, int col, int n)
{
	if(col == n)
	{
		print(board, n);
		return ;
	}
	for(int row = 0; row < n; row++)
	{
		if(check(board, col, row) == 0)
		{
			board[col] = row;
			solve(board, col + 1, n);
		}
	}

}

int main(int ac, char **av)
{
	if (ac != 2)   
        return (1);
	int n = atoi(av[1]);
	int *board = malloc(sizeof(int) * n);
	if (!board)                
        return (1); 
	solve(board, 0, n);
	free(board);
	return (0);  
}
