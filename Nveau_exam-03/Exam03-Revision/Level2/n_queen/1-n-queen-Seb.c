#include <stdio.h>          // Pour fprintf
#include <stdlib.h>         // Pour atoi, calloc, free
#include "queen-Seb.h"      // Header personnalisé
int abs(int a)              // Fonction valeur absolue (car abs() standard non autorisée)
{
    return (a < 0 ? -a : a);    // Si négatif retourne -a, sinon retourne a
}

void	print(int *pos, int n)  // Fonction d'affichage d'une solution
{
    int i;                      // Variable de boucle
    for (i = 0; i < n; i++)     // Parcourt chaque colonne
    {
        fprintf(stdout, "%d", pos[i]);  // Affiche position reine colonne i
        if (i < n - 1)                  // Si pas dernière colonne
            fprintf(stdout, " ");       // Ajoute espace entre nombres
    }
    fprintf(stdout, "\n");      // Saut de ligne final
}

void	solve(int n, int col, int *pos)  // Fonction récursive de résolution
{
    if (col == n)               // Cas de base: toutes colonnes remplies
    {
        print(pos, n);          // Affiche la solution trouvée
        return;                 // Retourne pour chercher autres solutions
    }
    for (int row = 0; row < n; row++)  // Teste chaque ligne colonne actuelle
    {
        int safe = 1;           // Flag sécurité position
        for (int c = 0; c < col; c++)  // Vérifie conflits reines déjà placées
        {
            if (pos[c] == row || abs(pos[c] - row) == col -c)  // Même ligne OU même diagonale
            {
                safe = 0;       // Position dangereuse
                break;          // Sort de la vérification
            }
        }
        if (safe)               // Si position sûre
        {
            pos[col] = row;     // Place reine cette position
            solve(n, col + 1, pos);  // Récursion colonne suivante
        }                       // Backtrack implicite (pos[col] écrasé)
    }
}

int main(int ac, char **av)     // Fonction principale
{
    if (ac != 2)                // Vérifie nombre arguments exact
        return (1);             // Erreur si pas 2 arguments
    int n = atoi(av[1]);        // Convertit argument en entier
    if (n < 1)                  // Si n invalide (négatif ou 0)
        return (0);             // Sort sans erreur ni affichage
    int *pos = calloc(n, sizeof(int));  // Alloue tableau positions (initialisé 0)
    if (!pos)                   // Vérifie succès allocation
        return (1);             // Erreur allocation mémoire
    solve(n, 0, pos);           // Lance résolution depuis colonne 0
    return (free(pos), 0);      // Libère mémoire ET retourne succès
}

/********************************************************/
// SANS LES COMMENTAIRES

#include <stdio.h>        
#include <stdlib.h>      
#include "queen-Seb.h"  
int abs(int a)          
{
    return (a < 0 ? -a : a);  
}

void	print(int *pos, int n) 
{
    int i;                   
    for (i = 0; i < n; i++) 
    {
        fprintf(stdout, "%d", pos[i]);  
        if (i < n - 1)                  
            fprintf(stdout, " ");     
    }
    fprintf(stdout, "\n");   
}

void	solve(int n, int col, int *pos) 
{
    if (col == n)              
    {
        print(pos, n);       
        return;               
    }
    for (int row = 0; row < n; row++)  
    {
        int safe = 1;         
        for (int c = 0; c < col; c++) 
        {
            if (pos[c] == row || abs(pos[c] - row) == col -c) 
            {
                safe = 0;     
                break;        
            }
        }
        if (safe)         
        {
            pos[col] = row;   
            solve(n, col + 1, pos);  
        }                      
    }
}

int main(int ac, char **av)  
{
    if (ac != 2)             
        return (1);      
    int n = atoi(av[1]); 
    if (n < 1)          
        return (0);      
    int *pos = calloc(n, sizeof(int));  
    if (!pos) 
        return (1); 
    solve(n, 0, pos);
    return (free(pos), 0);
}