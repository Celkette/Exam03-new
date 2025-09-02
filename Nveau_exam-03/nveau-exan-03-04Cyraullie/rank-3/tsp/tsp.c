#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <float.h>

#define MAX_CITIES 11

// Structure pour représenter une ville
typedef struct s_city {
    float x;
    float y;
} t_city;

// Fonction pour calculer la distance euclidienne entre deux villes
float calc_distance(t_city city1, t_city city2) {
    return sqrtf((city2.x - city1.x) * (city2.x - city1.x) +
                 (city2.y - city1.y) * (city2.y - city1.y));
}

// Fonction pour calculer la distance totale d'un trajet donné
float calc_total_distance(t_city *cities, int *route, int num_cities) {
    float total_distance = 0.0;
    for (int i = 0; i < num_cities - 1; i++) {
        total_distance += calc_distance(cities[route[i]], cities[route[i + 1]]);
    }
    total_distance += calc_distance(cities[route[num_cities - 1]], cities[route[0]]);
    return total_distance;
}

// Fonction pour échanger deux éléments dans un tableau
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Fonction pour générer toutes les permutations de villes (brute-force)
void permute(int *route, int left, int right, t_city *cities, int num_cities, float *min_distance, int *best_route) {
    if (left == right) {
        float dist = calc_total_distance(cities, route, num_cities);
        if (dist < *min_distance) {
            *min_distance = dist;
            for (int i = 0; i < num_cities; i++) {
                best_route[i] = route[i];
            }
        }
    } else {
        for (int i = left; i <= right; i++) {
            swap(&route[left], &route[i]);
            permute(route, left + 1, right, cities, num_cities, min_distance, best_route);
            swap(&route[left], &route[i]); // backtrack
        }
    }
}

// Fonction pour lire les villes depuis l'entrée standard avec getline
int read_cities(t_city *cities) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int num_cities = 0;

    // Lire l'entrée standard ligne par ligne
    while ((read = getline(&line, &len, stdin)) != -1 && num_cities < MAX_CITIES) {
        // Remplacer la virgule par un espace ou gérer la lecture avec sscanf
        if (sscanf(line, "%f, %f", &cities[num_cities].x, &cities[num_cities].y) == 2) {
            num_cities++;
        }
    }

    free(line);
    return num_cities;
}


int main() {
    t_city cities[MAX_CITIES];
    int num_cities = read_cities(cities);

    if (num_cities < 2) {
        fprintf(stderr, "There must be at least 2 cities.\n");
        return 1;
    }

    int route[MAX_CITIES];
    for (int i = 0; i < num_cities; i++) {
        route[i] = i;
    }

    float min_distance = FLT_MAX;
    int best_route[MAX_CITIES];

    permute(route, 0, num_cities - 1, cities, num_cities, &min_distance, best_route);

    printf("Shortest path distance: %.2f\n", min_distance);

    return 0;
}
