
#ifndef N_QUEENS_H
#define N_QUEENS_H

#include <stdio.h>
#include <stdlib.h>

/* Lance la résolution pour la colonne `col` */
void    solve(int *board, int n, int col);
/* Vérifie si on peut placer une reine en (col, row) */
int     is_safe(int *board, int col, int row);
/* Affiche une solution complète stockée dans `board` */
void    print_solution(int *board, int n);

#endif