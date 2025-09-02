#include "repaired_gnl.h"

char *ft_strchr(char *s, int c)
{
    int i = 0;                      // Initialise l'index à 0
    while (s[i] && s[i] != c)       // Parcourt la chaîne tant qu'on n'atteint pas '\0' ou le caractère cherché
        i++;                        // Incrémente l'index
    if (s[i] == c)                  // Si on a trouvé le caractère
        return (s + i);             // Retourne un pointeur vers sa position
    else
        return (NULL);              // Sinon retourne NULL
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
    size_t i = 0;                   // Initialise le compteur
    while (i < n)                   // Tant qu'on n'a pas copié n octets
    {
        ((char *)dest)[i] = ((char *)src)[i];  // Copie l'octet i de src vers dest
        i++;                        // Passe à l'octet suivant
    }
    return (dest);                  // Retourne le pointeur destination
}

size_t ft_strlen(char *s)
{
    size_t ret = 0;                 // Initialise le compteur de longueur
	if (!s)							// protection contre pointeur NULL
        return (0);
	while (*s)                      // Tant qu'on n'atteint pas '\0'
    {
        s++;                        // Avance dans la chaîne
        ret++;                      // Incrémente le compteur
    }
    return (ret);                   // Retourne la longueur
}

int	str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t	size1 = *s1 ? ft_strlen(*s1) : 0;// Calcule la taille de s1 (0 si NULL)
/*	size_t	size1;
	if (*s1)
   		size1 = ft_strlen(*s1);
	else
   		size1 = 0;
*/
    char *tmp = malloc(size2 + size1 + 1);    // Alloue de la mémoire pour les deux chaînes + '\0'
    if (!tmp)                       // Si l'allocation échoue
        return (0);                 // Retourne 0 (échec)
    if (*s1)                        // Si s1 existe
        ft_memcpy(tmp, *s1, size1); // Copie s1 dans tmp
    ft_memcpy(tmp + size1, s2, size2);        // Copie size2 octets de s2 après s1
    tmp[size1 + size2] = 0;         // Termine la chaîne par '\0'
    free(*s1);                      // Libère l'ancienne chaîne s1
    *s1 = tmp;                      // s1 pointe maintenant vers la nouvelle chaîne
    return (1);                     // Retourne 1 (succès)
}

int	str_append_str(char **s1, char *s2)
{
	return (str_append_mem(s1, s2, ft_strlen(s2)));  // Appelle str_append_mem avec la longueur complète de s2
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
    if (dest < src)                 // Si dest est avant src (pas de chevauchement dangereux)
        return (ft_memcpy(dest, src, n));  // Utilise memcpy normal
    else if (dest == src)           // Si dest et src sont identiques
        return (dest);              // Rien à faire
    size_t i = n;                   // Initialise i à n pour copier à l'envers
    while (i > 0)                   // Tant qu'il reste des octets à copier
    {
        i--;                        // Décrémente d'abord (copie de la fin vers le début)
        ((char *)dest)[i] = ((char *)src)[i];  // Copie l'octet à l'index i
    }
    return (dest);                  // Retourne dest
}

char	*get_next_line(int fd)
{
    static char b[BUFFER_SIZE + 1] = "";  // Buffer statique pour garder les données entre appels
    char *ret = NULL;               // Pointeur vers la ligne à retourner (initialement NULL)

    char *tmp = ft_strchr(b, '\n'); // Cherche un '\n' dans le buffer
    while (!tmp)                    // Tant qu'il n'y a pas de '\n' dans le buffer
    {
        if (!str_append_str(&ret, b))     // Ajoute le contenu du buffer à ret
            return (NULL);          // Si échec, retourne NULL
        b[0] = '\0';                // Vide le buffer (met le premier caractère à '\0')
        int read_ret = read(fd, b, BUFFER_SIZE);  // Lit BUFFER_SIZE octets depuis le fichier
        if (read_ret == -1)         // Si erreur de lecture
            return (NULL);          // Retourne NULL
        if (read_ret == 0)          // Si fin de fichier
            break;                  // Sort de la boucle
        b[read_ret] = 0;            // Termine le buffer par '\0'
        tmp = ft_strchr(b, '\n');   // Cherche à nouveau un '\n' dans le nouveau contenu
    }
    if (tmp)                        // Si on a trouvé un '\n'
    {
        if (!str_append_mem(&ret, b, tmp - b + 1))  // Ajoute les caractères jusqu'au '\n' inclus
        {
            free(ret);              // Si échec, libère ret
            return (NULL);          // Retourne NULL
        }
        ft_memmove(b, tmp + 1, ft_strlen(tmp + 1) + 1);  // Déplace le reste du buffer au début
    }
    else                            // Si pas de '\n' (fin de fichier)
    {
        b[0] = '\0';                // Vide le buffer
        if (!ret || !*ret)          // Si ret est NULL ou vide
        {
            free(ret);              // Libère ret
            return (NULL);          // Retourne NULL (fin de fichier)
        }
    }
    return (ret);                   // Retourne la ligne lue
}

#include <stdio.h>
#include <fcntl.h>
int main(void)
{
    int fd = open("test.txt", O_RDONLY);     // Ouvre le fichier en lecture seule
    char *line;                     // Pointeur pour stocker chaque ligne

    while ((line = get_next_line(fd)) != NULL)  // Lit le fichier ligne par ligne
    {
        printf("%s", line);         // Affiche la ligne
        free(line);                 // Libère la mémoire de la ligne
    }
    close(fd);                      // Ferme le fichier
    return (0);                     // Fin du programme
}
