#include <stdio.h>   // Pour fprintf, perror
#include <string.h>  // Pour strlen
#include <unistd.h>  // Pour read, write, STDIN_FILENO, STDOUT_FILENO
#include <stdlib.h>  // Pour malloc, free

// Définit la taille maximale du buffer. On ajoute +1 pour le terminateur null,
// garantissant qu'on peut stocker jusqu'à 10k octets de contenu réel en sécurité.
#define MAX_BUFF_SIZE (10000 + 1)

// Fonction ft_strncmp personnalisée :
// Compare les 'n' premiers caractères de deux chaînes.
// Retourne 1 si tous les 'n' caractères correspondent, 0 sinon.
// Note : C'est un strncmp simplifié qui vérifie seulement l'égalité,
int ft_strncmp(char *s1, char *s2, int n) {
    int i = 0;
    // Boucle tant que 'i' est dans les limites de 'n' et que les caractères à s1[i] et s2[i] sont identiques.
    while (i < n && s1[i] == s2[i]) {
        i++;
    }
    // Si 'i' a atteint 'n', cela signifie que tous les 'n' caractères correspondent.
    if (i == n) 
        return 1;
    else
        return 0; // Différence trouvée ou 'n' caractères non atteints.
}

int main(int ac, char **av) {
// --- 1. Gestion des arguments (GESTION D'ERREUR IMPORTANTE) ---
    // Le programme nécessite exactement un argument (argc == 2).
    // L'argument ne doit pas être NULL et sa longueur doit être supérieure à 0.
    if (ac != 2 || av[1] == NULL || strlen(av[1]) == 0) {
        return 1; // Retourne 1 comme spécifié pour un usage incorrect des arguments.
    }

// --- 2. Allocation mémoire ---
    // Alloue un grand buffer pour stocker toute l'entrée depuis stdin.
    // MAX_BUFF_SIZE inclut l'espace pour le terminateur null.
    char *buff = malloc(MAX_BUFF_SIZE);

    // --- Gestion d'erreur Malloc (GESTION D'ERREUR IMPORTANTE) ---
    // Vérifie si malloc a échoué. S'il retourne NULL, l'allocation mémoire a échoué.
    if (buff == NULL) {
//        fprintf(stderr, "Error: "); // Affiche "Error: " sur la sortie d'erreur standard.
        perror("Error: ");             // Affiche le message d'erreur du système (ex: "Cannot allocate memory").
        return 1;                   // Retourne 1 comme spécifié pour les erreurs malloc.
    }

    char *str_occurence = av[1];           // Pointeur vers la chaîne de recherche (ex: "bonjour")
    char current_char;                  // Stockage temporaire pour un seul caractère lu depuis stdin
    ssize_t bytes_read_result;          // Stocke la valeur de retour de read() (nombre d'octets lus, 0 pour EOF, -1 pour erreur)
    int buff_idx = 0;                   // Index pour suivre la position courante dans 'buff' pendant la lecture
    int occurence_len = strlen(str_occurence); // Longueur de la chaîne de recherche

// --- 3. Première boucle : Lit toute l'entrée depuis stdin dans 'buff' ---
    // Lit un caractère à la fois jusqu'à EOF (bytes_read_result == 0),
    // qu'une erreur survienne (bytes_read_result == -1), ou que le buffer soit plein.
    while ((bytes_read_result = read(STDIN_FILENO, &current_char, 1)) > 0) {
        // Prévient le débordement de buffer : Arrête la lecture si on est sur le point de dépasser l'espace alloué.
        // MAX_BUFF_SIZE - 1 garantit qu'on a toujours de la place pour le terminateur null.
        if (buff_idx >= MAX_BUFF_SIZE - 1) {
            break; // Buffer plein, arrête la lecture.
        }
        buff[buff_idx++] = current_char; // Stocke le caractère dans 'buff' et incrémente l'index.
    }

    // --- Gestion d'erreur de lecture (IMPORTANT) ---
    // Après la boucle de lecture, vérifie si la dernière opération de lecture a résulté en une erreur.
    if (bytes_read_result == -1) {
//        fprintf(stderr, "Error: "); // Affiche "Error: " sur la sortie d'erreur standard.
        perror("Error: ");                 // Affiche le message d'erreur du système.
        free(buff);                 // Libère la mémoire allouée avant de quitter.
        return 1;                   // Retourne 1 comme spécifié pour les erreurs de lecture.
    }

    // --- Termine le buffer par null ---
    // C'est crucial pour les fonctions de chaîne comme ft_strncmp qui se fient aux limites de chaîne.
    // 'buff_idx' contient maintenant le nombre total de caractères lus avec succès.
    buff[buff_idx] = '\0';

// --- 4. Deuxième boucle : Traite 'buff' et écrit sur stdout ---
    int process_idx = 0; // Index pour itérer à travers 'buff' pour le traitement et la sortie.
    while (buff[process_idx] != '\0') { // Boucle jusqu'à ce que le terminateur null soit atteint (fin de l'entrée valide).
        // Vérifie une correspondance de 'str_occurence' commençant à 'buff[process_idx]' :
        // 1. S'assure qu'il y a assez de caractères restants dans la partie *valide* de 'buff'
        //    pour une correspondance complète de 'str_occurence'. (process_idx + occurence_len <= buff_idx)
        // 2. Appelle ft_strncmp pour comparer la sous-chaîne avec 'str_occurence'.
        if (process_idx + occurence_len <= buff_idx &&
            ft_strncmp(&buff[process_idx], str_occurence, occurence_len) == 1)
        {
            // Si une correspondance est trouvée :
            // Écrit 'occurence_len' nombre d'astérisques sur la sortie standard.
            int y = 0;
            while (y < occurence_len) 
            {
                write(STDOUT_FILENO, "*", 1);
                y++;
                process_idx++;
            }
        } 
        else 
        {
            // Si aucune correspondance à la position courante :
            // Écrit le caractère courant de 'buff' sur la sortie standard.
            write(STDOUT_FILENO, &buff[process_idx], 1); // écrit le caractère lui-même.
            // Avance l'index de traitement d'un caractère.
            process_idx++;
        }
    }

// --- 5. Nettoyage mémoire ---
    free(buff); // Libère la mémoire allouée dynamiquement avant
}

/******************************************************/
// SANS COMMENTAIRES
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_BUFF_SIZE (10000 + 1)

int ft_strncmp(char *s1, char *s2, int n) 
{
    int i = 0;
    while (i < n && s1[i] == s2[i]) {
        i++;
    }
    if (i == n) {
        return 1;
    } else {
        return 0;
    }
}

int main(int ac, char **av) {
    if (ac != 2 || av[1] == NULL || strlen(av[1]) == 0) {
        return 1;
    }

    char *buff = (char *)malloc(MAX_BUFF_SIZE);

    if (buff == NULL) {
        fprintf(stderr, "Error: ");
        perror("");
        return 1;
    }

    char *str_occurence = av[1];
    char current_char;
    ssize_t bytes_read_result;
    int buff_idx = 0;
    int occurence_len = strlen(str_occurence);

    while ((bytes_read_result = read(STDIN_FILENO, &current_char, 1)) > 0) {
        if (buff_idx >= MAX_BUFF_SIZE - 1) {
            break;
        }
        buff[buff_idx++] = current_char;
    }

    if (bytes_read_result == -1) {
        fprintf(stderr, "Error: ");
        perror("");
        free(buff);
        return 1;
    }

    buff[buff_idx] = '\0';

    int process_idx = 0;
    while (buff[process_idx] != '\0') {
        if (process_idx + occurence_len <= buff_idx &&
            ft_strncmp(&buff[process_idx], str_occurence, occurence_len) == 1)
        {
            for (int y = 0; y < occurence_len; y++) {
                write(STDOUT_FILENO, "*", 1);
            }
            process_idx += occurence_len;
        } else {
            write(STDOUT_FILENO, &buff[process_idx], 1);
            process_idx++;
        }
    }

    free(buff);
    return 0;
}

/******************************************************/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_BUFF_SIZE (10000 + 1)

int ft_strncmp(char *s1, char *s2, int n) 
{
    int i = 0;
    while (i < n && s1[i] == s2[i]) {
        i++;
    }
    if (i == n) {
        return 1;
    } else {
        return 0;
    }
}

int main(int ac, char **av) {
    if (ac != 2 || av[1] == NULL || strlen(av[1]) == 0) {
        return 1;
    }

    char *buff = malloc(MAX_BUFF_SIZE);

    if (buff == NULL) 
    {
        perror("Error: ");
        return 1;
    }

    char *str_occurence = av[1];
    char current_char;
    ssize_t bytes_read_result;
    int buff_idx = 0;
    int occurence_len = strlen(str_occurence);

    //(read(fd de l'entree standard, adresse du stckage du char,lecture de 1 octet))
    while ((bytes_read_result = read(STDIN_FILENO, &current_char, 1)) > 0) 
    {
        if (buff_idx >= MAX_BUFF_SIZE - 1) 
            break;
        buff[buff_idx] = current_char;
        buff_idx++;
    }

    if (bytes_read_result == -1) {
        fprintf(stderr, "Error: ");
        perror("");
        free(buff);
        return 1;
    }

    buff[buff_idx] = '\0';

    int process_idx = 0;
    while (buff[process_idx] != '\0') {
        if (process_idx + occurence_len <= buff_idx &&
            ft_strncmp(&buff[process_idx], str_occurence, occurence_len) == 1)
        {
            for (int y = 0; y < occurence_len; y++) {
                write(STDOUT_FILENO, "*", 1);
            }
            process_idx += occurence_len;
        } else {
            write(STDOUT_FILENO, &buff[process_idx], 1);
            process_idx++;
        }
    }

    free(buff);
    return 0;
}