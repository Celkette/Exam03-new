#include <stdio.h>      // Inclusion pour fprintf
#include <stdlib.h>     // Inclusion pour atoi, malloc, free

// Affiche une solution trouvée
void	print_solution(int *board, int n)
{
    for (int i = 0; i < n; i++)                  // Parcourt chaque colonne
    {
        fprintf(stdout, "%d", board[i]);         // Affiche la ligne de la reine dans la colonne i
        if (i < n - 1)                           // Si ce n'est pas la dernière colonne
            fprintf(stdout, " ");                // Ajoute un espace
    }
    fprintf(stdout, "\n");                       // Saut de ligne à la fin
}

// Vérifie si la position (row, col) est sûre pour placer une reine
int	is_safe(int *board, int col, int row)
{
    for (int i = 0; i < col; i++)                // Parcourt les colonnes déjà remplies
    {
        // Vérifie même ligne ou même diagonale
        if (board[i] == row || abs(board[i] - row) == col - i)
            return 0;                            // Position non sûre
    }
    return 1;                                    // Position sûre
}

// Algorithme récursif de backtracking pour placer les reines
void	solve(int *board, int col, int n)
{
    if (col == n)                                // Cas de base : toutes les colonnes sont remplies
    {
        print_solution(board, n);                // Affiche la solution trouvée
        return;
    }
    for (int row = 0; row < n; row++)            // Essaie chaque ligne pour la colonne courante
    {
        if (is_safe(board, col, row))            // Si la position est sûre
        {
            board[col] = row;                    // Place la reine
            solve(board, col + 1, n);            // Récursion pour la colonne suivante
        }
    }
}

// Fonction valeur absolue (car abs standard non autorisée)
int	abs(int n)
{
    return (n < 0 ? -n : n);                     // Retourne la valeur absolue de n
}

// Fonction principale
int	main(int ac, char **av)
{
    if (ac != 2)                                 // Vérifie le nombre d'arguments
        return (1);                              // Erreur si mauvais nombre d'arguments
    int n = atoi(av[1]);                         // Convertit l'argument en entier
    if (n < 4)                                   // Si n < 4, aucune solution à afficher
        return (0);                              // Sort sans affichage
    int *board = malloc(sizeof(int) * n);        // Alloue le tableau des positions
    if (!board)                                  // Vérifie l'allocation mémoire
        return (1);                              // Erreur allocation
    solve(board, 0, n);                          // Lance la résolution
    free(board);                                 // Libère la mémoire
    return (0);                                  // Succès
}

/********************************************************/
// SANS LES COMMENTAIRES
#include <stdio.h>
#include <stdlib.h>

void	print_solution(int *board, int n)
{
    for (int i = 0; i < n; i++)
    {
        fprintf(stdout, "%d", board[i]);
        if (i < n - 1)
            fprintf(stdout, " ");
    }
    fprintf(stdout, "\n");
}

int	is_safe(int *board, int col, int row)
{
    for (int i = 0; i < col; i++)
    {
        if (board[i] == row || abs(board[i] - row) == col - i)
            return 0;
    }
    return 1;
}

void	solve(int *board, int col, int n)
{
    if (col == n)
    {
        print_solution(board, n);
        return;
    }
    for (int row = 0; row < n; row++)
    {
        if (is_safe(board, col, row))
        {
            board[col] = row;
            solve(board, col + 1, n);
        }
    }
}

int	abs(int n)
{
    return (n < 0 ? -n : n);
}

int	main(int ac, char **av)
{
    if (ac != 2)
        return (1);
    int n = atoi(av[1]);
    if (n < 4)
        return (0);
    int *board = malloc(sizeof(int) * n);
    if (!board)
        return (1);
    solve(board, 0, n);
    free(board);
    return (0);
}


