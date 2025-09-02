/*
	PENSER A AJOUTER DANS .h
# include <stdlib.h>
# include <unistd.h>
*/

#include "broken_gnl-Corrigé.h"

//Trouve la 1ère occurrence d'un caractère dans une chaîne
char	*ft_strchr(char *s, int c)
{
    int	i = 0; // Initialise l'index de parcours

    while (s[i] && s[i] != c) // Tant que pas fin de chaîne ET caractère différent de celui recherché
        i++; // Incrémente l'index
    if (s[i] == c) // Si on a trouvé le caractère recherché
        return (s + i); // Retourne pointeur vers le caractère trouvé
//ou	return (&s[i]); // Autre syntaxe équivalente
    else
        return (NULL); // Sinon retourne NULL (pas trouvé)
}
//Copie n octets de src vers dest (sans gérer le chevauchement)
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
    size_t i = 0; // Index pour parcourir les octets à copier

    while (i < n) // Tant qu'on n'a pas copié n octets
    {
        ((char *)dest)[i] = ((char *)src)[i]; // Copie octet par octet (cast en char)
        i++; // Passe à l'octet suivant
    }
    return (dest); // Retourne le pointeur destination
}

size_t	ft_strlen(char *s)
{
    size_t	ret = 0; // Compteur de caractères
    if (!s) // Si pointeur NULL
        return (0); // Retourne longueur 0
    while (*s) // Tant qu'on n'atteint pas '\0'
    {
        s++; // Avance dans la chaîne
        ret++; // Incrémente le compteur
    }
    return (ret); // Retourne la longueur calculée
}
//Concatène s2 (size2 octets) à la fin de s1
int	str_append_mem(char **s1, char *s2, size_t size2)
{
    if (*s1) // Si s1 existe déjà
        size_t	size1 = ft_strlen(*s1); // Calcule sa longueur
    else
        size_t	size1 = 0; // Sinon longueur = 0
//(ou size_t	size1 = *s1 ? ft_strlen(*s1) : 0;) // Version condensée
    char	*tmp = malloc(size2 + size1 + 1); // Alloue mémoire pour nouvelle chaîne (taille1 + taille2 + '\0')
                //ou  char *tmp = malloc(sizeof(char)*(size2 + size1 + 1)); // Syntaxe alternative
    if (!tmp) // Si allocation échoue
        return (0); // Retourne erreur
    if (*s1) // Si s1 existe
        ft_memcpy(tmp, *s1, size1); // Copie s1 au début de tmp
    ft_memcpy(tmp + size1, s2, size2); // Copie s2 après s1 dans tmp
            //ou  ft_memcpy(&tmp[size1], s2, size2); // Syntaxe alternative
    tmp [size1 + size2] = 0; // Ajoute le caractère de fin '\0'
    free(*s1); // Libère l'ancienne chaîne s1
    *s1 = tmp; // s1 pointe maintenant vers la nouvelle chaîne
    return (1); // Retourne succès
}
//Version simplifiée de str_append_mem pour chaînes complètes
int	str_append_str(char **s1, char *s2)
{
    return (str_append_mem(s1, s2, ft_strlen(s2))); // Appelle str_append_mem avec la longueur de s2
}
//idem memcpy mais perment le chevauchement
//char tab[10] = "abcdefghi";
//memmove(tab + 2, tab, 5);
// tab devient : "ababcdehi"
//src = tab → "abcde"
//dest = tab + 2 → "cdefg..."
//Copie n octets en gérant le chevauchement mémoire
void	*ft_memmove(void *dest, const void *src, size_t n)
{
    if (dest < src) // Si dest est avant src en mémoire
        return (ft_memcpy(dest, src, n)); // Pas de chevauchement, utilise memcpy normal
    else if (dest == src /*|| n == 0*/) // Si dest et src pointent vers la même adresse
        return (dest); // Rien à faire, retourne dest
    size_t	i = n; // Commence par la fin pour éviter l'écrasement
    while (i > 0) // Copie de la fin vers le début
    {
        i--; // Décrémente l'index (copie en sens inverse)
        ((char *)dest)[i] = ((char *)src)[i]; // Copie l'octet i
    }
    return (dest); // Retourne le pointeur destination
}
//Lit une ligne complète depuis un descripteur de fichier
char	*get_next_line(int fd)
{
    static char	buff[BUFFER_SIZE + 1] = ""; // Buffer statique pour garder les données entre appels
    char	*ret; // Chaîne de retour (la ligne à retourner)
    int	read_ret;
    char	*tmp;

    ret = NULL;
    tmp = ft_strchr(buff, '\n'); // Cherche un '\n' dans le buffer
    
    while (!tmp) // Tant qu'on n'a pas trouvé de '\n'
    {
        if (!str_append_str(&ret, buff)) // Ajoute le contenu du buffer à ret
            return (NULL); // Si erreur d'allocation, retourne NULL
        read_ret = read(fd, buff, BUFFER_SIZE); // Lit BUFFER_SIZE octets depuis le fichier
        if (read_ret == -1) // Si erreur de lecture
            return (NULL); // Retourne NULL
        if (read_ret == 0) // Si fin de fichier atteinte
            break; // Sort de la boucle
        buff[read_ret] = 0; // Ajoute '\0' à la fin des données lues
        tmp = ft_strchr(buff, '\n'); // Recherche à nouveau un '\n'
    }
    if (tmp) // Si on a trouvé un '\n'
    {
        if (!str_append_mem(&ret, buff, tmp - buff + 1)) // Ajoute la partie jusqu'au '\n' (inclus)
        {
            free(ret); // Si erreur, libère ret
            return (NULL); // Retourne NULL
        }
        ft_memmove(buff, tmp + 1, ft_strlen(tmp + 1) + 1); // Décale le reste du buffer vers le début
    }
    else // Si pas de '\n' trouvé (fin de fichier)
    {
        buff[0] = '\0'; // Vide le buffer
        if (!ret || !*ret) // Si ret est NULL ou si pointe sur chaine vide
        {
            free(ret); // Libère ret
            return (NULL); // Retourne NULL (plus rien à lire)
        }
    }
    return (ret); // Retourne la ligne lue
}

#include <stdio.h>
#include <fcntl.h>
int main(void)
{
	int fd = open("test.txt", O_RDONLY);
	char *line;

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}