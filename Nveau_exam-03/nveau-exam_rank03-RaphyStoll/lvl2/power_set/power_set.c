/* power_set1.c */
#include "power_set.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static int target;     /* somme recherchée */
static int *nums;      /* tableau des éléments de l'ensemble */
static int n;          /* nombre d'éléments */
static int *subset;    /* tableau pour la sous-suite courante */
static int subset_size;/* taille de la sous-suite courante */

/*
 * backtrack parcourt récursivement tous les sous-ensembles
 * en commençant à l'indice 'start', en gardant la somme actuelle
 * current_sum. Dès que current_sum == target, on affiche subset.
 */
void backtrack(int start, int current_sum) {
    if (current_sum == target) {
        /* afficher la sous-suite (ou ligne vide si subset_size==0) */
        if (subset_size == 0) {
            printf("\n");
        } else {
            printf("%d", subset[0]);
            for (int i = 1; i < subset_size; i++)
                printf(" %d", subset[i]);
            printf("\n");
        }
    }
    for (int i = start; i < n; i++) {
        subset[subset_size++] = nums[i];
        backtrack(i + 1, current_sum + nums[i]);
        subset_size--;
    }
}

int main(int argc, char **argv) {
    if (argc < 2)
        return 0;

    /* lire la somme cible */
    target = atoi(argv[1]);

    /* nombre d'éléments dans l'ensemble */
    n = argc - 2;

    /* allocation des tableaux */
    nums = malloc(sizeof(int) * n);
    if (!nums) exit(1);

    subset = malloc(sizeof(int) * n);
    if (!subset) exit(1);

    /* parser les éléments */
    for (int i = 0; i < n; i++)
        nums[i] = atoi(argv[i + 2]);

    subset_size = 0;
    backtrack(0, 0);

    free(nums);
    free(subset);
    return 0;
}