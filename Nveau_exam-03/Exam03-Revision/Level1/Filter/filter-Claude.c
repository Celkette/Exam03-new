#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc != 2 || !argv[1][0])// Vérification 1 arguments non vide
        return 1;
	char *pattern = argv[1];        // Pointe vers le pattern à chercher
	int pattern_len = strlen(pattern);  // Calcule la longueur du pattern
	char c;                         // Variable pour lire un caractère à la fois
	char *buffer = malloc(pattern_len); // Alloue un buffer de la taille exacte du pattern
	if (!buffer)                    // Vérifie si l'allocation a réussi
	{
		perror("Error: ");          // Affiche l'erreur système
		return 1;                   // Termine le programme avec code d'erreur
	}
	int buffer_pos = 0;             // Position courante dans le buffer (nombre de caractères stockés)
// Boucle de lecture principale    
	while (read(0, &c, 1) > 0)      // Lit 1 caractère depuis stdin, continue tant qu'il y a des données
	{
		buffer[buffer_pos] = c;     // Stocke le caractère lu dans le buffer
		buffer_pos++;               // Incrémente la position dans le buffer
// Vérification quand le buffer est plein
		if (buffer_pos == pattern_len)  // Si le buffer contient autant de caractères que le pattern
		{
			int match = 1;              // Flag pour indiquer si on a trouvé une correspondance
			for (int i = 0; i < pattern_len; i++)  // Compare chaque caractère du buffer avec le pattern
			{
				if (buffer[i] != pattern[i])    // Si un caractère ne correspond pas
				{
					match = 0;          // La correspondance échoue
					break;              // Sort de la boucle de comparaison
				}
			}
// Traitement selon la correspondance
            if (match)                  // Si le buffer correspond exactement au pattern
			{
				for (int i = 0; i < pattern_len; i++)  // Affiche autant d'étoiles que la longueur du pattern
					printf("*");
			}
			else                        // Si le buffer ne correspond pas au pattern
			{
				printf("%c", buffer[0]); // Affiche seulement le premier caractère du buffer
				for (int i = 0; i < pattern_len - 1; i++)  // Décale tous les caractères d'une position vers la gauche
					buffer[i] = buffer[i + 1];
				buffer_pos--;           // Réduit la position car on a libéré une place en début de buffer
			}
		}
	}
// Affichage des caractères restants
    for (int i = 0; i < buffer_pos; i++)  // Après la fin de lecture, affiche tous les caractères restants dans le buffer
		printf("%c", buffer[i]);
	free(buffer);                   // Libère la mémoire allouée pour le buffer
	return 0;                       // Termine le programme avec succès
}

/************************************************************/
//SANS COMMENTAIRES

int main(int argc, char **argv)
{
    // Vérification des arguments
    if (argc != 2 || !argv[1][0])
        return 1;
    
    char *pattern = argv[1];
    int pattern_len = strlen(pattern);
    
    // Buffer pour lire caractère par caractère
    char c;
    char *buffer = malloc(pattern_len);
    if (!buffer)
    {
        perror("Error: ");
        return 1;
    }
    
    int buffer_pos = 0;
    
    // Lire caractère par caractère depuis stdin
    while (read(0, &c, 1) > 0)// Lire caractère par caractère depuis stdin
    {
        buffer[buffer_pos] = c;
        buffer_pos++;
        // Si le buffer est plein, vérifier s'il correspond au pattern
        if (buffer_pos == pattern_len)
        {
            int match = 1;
            for (int i = 0; i < pattern_len; i++)
            {
                if (buffer[i] != pattern[i])
                {
                    match = 0;
                    break;
                }
            }
            if (match)
            {
                // Afficher des '*' à la place du pattern
                for (int i = 0; i < pattern_len; i++)
                    printf("*");
            }
            else
            {
                // Afficher le premier caractère du buffer
                printf("%c", buffer[0]);
                // Décaler le buffer d'une position
                for (int i = 0; i < pattern_len - 1; i++)
                    buffer[i] = buffer[i + 1];
                buffer_pos--;
            }
        }
    }
    // Afficher les caractères restants dans le buffer
    for (int i = 0; i < buffer_pos; i++)
        printf("%c", buffer[i]);
    
    free(buffer);
    return 0;
}

