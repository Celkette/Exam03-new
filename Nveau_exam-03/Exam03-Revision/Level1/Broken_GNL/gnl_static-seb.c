
#include "gnl_static-seb.h"

char *ft_strdup(char *src) {
	char *dest;
	int i = 0;
	while (src[i])
		i++;
	dest = malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while(src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char *get_next_line(int fd)
{
	static char buffer[BUFFER_SIZE];
	static int buf_pos;
	static int buf_read;
	int i = 0;
	char line[70000];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return NULL;
	while (1) {
		if (buf_pos >= buf_read)
		{
			buf_read = read(fd, buffer, BUFFER_SIZE);
			if (buf_read <= 0)
				break;
			buf_pos = 0;
		}
		line[i++] = buffer[buf_pos++];
		if (buffer[buf_pos] == '\n')
			break;
	}
	line[i] = '\0';
	if (i == 0)
		return (NULL);
	return (ft_strdup(line));
}

#include <stdio.h>
#include <fcntl.h>
int main(void)
{
	int fd = open("text.txt", O_RDONLY);
	char *line;

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}

/*******************************************************************************/
//AVEC COMMENTAIRES
char *get_next_line(int fd)
{
    static char buff[BUFFER_SIZE + 1] = ""; // Buffer statique pour stocker les données lues, partagé entre les appels
    char *ret = NULL;                       // Chaîne qui contiendra la ligne à retourner

    char *tmp = ft_strchr(buff, '\n');      // Cherche un saut de ligne dans le buffer
    while (!tmp)                            // Tant qu'il n'y a pas de saut de ligne dans le buffer
    {
        if (!str_append_str(&ret, buff))    // Ajoute le contenu du buffer à la ligne en cours (ret)
            return (NULL);                  // Si erreur d'allocation, retourne NULL
        int read_ret = read(fd, buff, BUFFER_SIZE); // Lit BUFFER_SIZE caractères depuis le fichier dans le buffer
        if (read_ret == -1)                 // Si erreur de lecture
            return (NULL);
        if (read_ret == 0)                  // Si fin de fichier atteinte
            break;
        buff[read_ret] = 0;                 // Termine le buffer par un caractère nul
        tmp = ft_strchr(buff, '\n');        // Cherche à nouveau un saut de ligne dans le buffer
    }
    if (tmp)                                // Si un saut de ligne a été trouvé
    {
        if (!str_append_mem(&ret, buff, tmp - buff + 1)) // Ajoute la partie du buffer jusqu'au saut de ligne à la ligne
        {
            free(ret);                      // Libère la mémoire en cas d'erreur
            return (NULL);
        }
        ft_memmove(buff, tmp + 1, ft_strlen(tmp + 1) + 1); // Décale le buffer pour enlever la ligne déjà lue
    }
    else                                    // Si pas de saut de ligne (fin de fichier)
    {
        buff[0] = '\0';                     // Vide le buffer
        if (!ret || !*ret)                  // Si la ligne est vide
        {
            free(ret);                      // Libère la mémoire
            return (NULL);                  // Retourne NULL
        }
    }
    return (ret);                           // Retourne la ligne lue
}
