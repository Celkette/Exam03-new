/*
	PENSER A AJOUTER DANS .h
# include <stdlib.h>
# include <unistd.h>
*/

#include "broken_gnl-Corrigé.h"

char	*ft_strchr(char *s, int c)
{
	int	i = 0;

	while (/*(s[i] &&*/ s[i] != c)// AJOUT: vérif s[i] pour éviter segfault
		i++;
	if (s[i] == c)
		return (s + i);
//ou	return (&s[i]);
	else
		return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
//	size_t i = 0;

	while (--n > 0)// A supprimer
//	while (i < n)
//	{
		((char *)dest)[n - 1] = ((char *)src)[n - 1];// A supprimer
//		((char *)dest)[i] = ((char *)src)[i];		
//		i++;
//	}
	return (dest);
}

size_t	ft_strlen(char *s)
{
	size_t	ret = 0;
//	if (!s)  // AJOUTÉ: protection contre pointeur NULL
//        return (0);
	while (*s)
	{
		s++;
		ret++;
	}
	return (ret);
}
//Elle concatène la chaîne pointée par *s1 (si elle existe) avec les size2 premiers caractères de s2.
//Elle alloue une nouvelle zone mémoire pour contenir les deux morceaux.
//Elle copie d’abord *s1 dans la nouvelle zone, puis size2 caractères de s2 juste après.
//Elle termine la nouvelle chaîne par \0.
//Elle libère l’ancienne chaîne *s1 et met à jour le pointeur.
//Elle retourne 1 en cas de succès, 0 en cas d’échec d’allocation.
int	str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t	size1;
	if (*s1)
		size1 = ft_strlen(*s1);
	else
		size1 = 0;
//(ou size_t	size1 = *s1 ? ft_strlen(*s1) : 0)
	char	*tmp = malloc(size2 + size1 + 1);
				//ou  char *tmp = malloc(sizeof(char)*(size2 + size1 + 1));
	if (!tmp)
		return (0);
	if (*s1)// AJOUT: vérification avant copie
		ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
			//ou  ft_memcpy(&tmp[size1], s2, size2);
	tmp [size1 + size2] = 0;
	free(*s1);
	*s1 = tmp;
	return (1);
}

int	str_append_str(char **s1, char *s2)
{
	return (str_append_mem(s1, s2, ft_strlen(s2)));
}
//idem memcpy mais permet le chevauchement
//char tab[10] = "abcdefghi";
//memmove(tab + 2, tab, 5);
// tab devient : "ababcdehi"
//src = tab → "abcde"
//dest = tab + 2 → "cdefg..."
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	//if (dest > src)// A supprimer
	if (dest < src)//si // On copie 5 char à partir de tab[2] ("cdefg") vers tab[0]
		return (ft_memcpy(dest, src, n));
	else if (dest == src /*|| n == 0*/)//si pointe sur la même adresse
		return (dest);
	//size_t	i = ft_strlen((char *)src) - 1;// A supprimer
	size_t	i = n;
	//while (i >= 0)// A supprimer
	while (i > 0)
	{
		i--; //en 1er (inverser avec ligne suivante)
		((char *)dest)[i] = ((char *)src)[i];
	}
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1] = "";
	char	*ret = NULL;

	char	*tmp = ft_strchr(buff, '\n');
	while (!tmp)
	{
		if (!str_append_str(&ret, buff))
			return (NULL);
		int	read_ret = read(fd, buff, BUFFER_SIZE);
		if (read_ret == -1)
			return (NULL);
		if (read_ret == 0)// AJOUTÉ: gestion fin de fichier
            break;
		buff[read_ret] = 0;
		tmp = ft_strchr(buff, '\n');
	}
	if (tmp)
	{
		if (!str_append_mem(&ret, buff, tmp - buff + 1))
		{
			free(ret);
			return (NULL);
		}
		ft_memmove(buff, tmp + 1, ft_strlen(tmp + 1) + 1);
	}
	else
	{
		buff[0] = '\0';
		if (!ret || !*ret)
		{
			free(ret);
			return (NULL);
		}
	}
	return (ret);
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
/************************************************************ */
// CORRECTION EN COMMENTAIRE
/*	PENSER A AJOUTER DANS .h
# include <stdlib.h>
# include <unistd.h>
*/

/*#include "broken_gnl-Corrigé.h"

char	*ft_strchr(char *s, int c)
{
	int	i = 0;
		  //s[i] &&			  // AJOUT: vérif s[i] pour éviter segfault
	while ((s[i] && s[i] != c)// AJOUT: vérif s[i] pour éviter segfault
		i++;
	if (s[i] == c)
		return (s + i);
//ou	return (&s[i]);
	else
		return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
//	size_t i = 0;

	while (--n > 0)// A supprimer
//	while (i < n)
//	{
		((char *)dest)[n - 1] = ((char *)src)[n - 1];// A supprimer
//		((char *)dest)[i] = ((char *)src)[i];		
//		i++;
//	}
	return (dest);
}

size_t	ft_strlen(char *s)
{
	size_t	ret = 0;
//	if (!s)  // AJOUTÉ: protection contre pointeur NULL
//        return (0);
	while (*s)
	{
		s++;
		ret++;
	}
	return (ret);
}
//Elle concatène la chaîne pointée par *s1 (si elle existe) avec les size2 premiers caractères de s2.
//Elle alloue une nouvelle zone mémoire pour contenir les deux morceaux.
//Elle copie d’abord *s1 dans la nouvelle zone, puis size2 caractères de s2 juste après.
//Elle termine la nouvelle chaîne par \0.
//Elle libère l’ancienne chaîne *s1 et met à jour le pointeur.
//Elle retourne 1 en cas de succès, 0 en cas d’échec d’allocation.
int	str_append_mem(char **s1, char *s2, size_t size2)
{
//	if (*s1)
		size_t	size1 = ft_strlen(*s1);
//	else
//		size_t	size1 = 0;
//(ou size_t	size1 = *s1 ? ft_strlen(*s1) : 0;)
	char	*tmp = malloc(size2 + size1 + 1);
				//ou  char *tmp = malloc(sizeof(char)*(size2 + size1 + 1));
	if (!tmp)
		return (0);
//	if (*s1)// AJOUT: vérification avant copie
		ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
			//ou  ft_memcpy(&tmp[size1], s2, size2);
	tmp [size1 + size2] = 0;
	free(*s1);// CORRIGÉ: free avant réassignation
	*s1 = tmp;
	return (1);
}

int	str_append_str(char **s1, char *s2)
{
	return (str_append_mem(s1, s2, ft_strlen(s2)));
}
//idem memcpy mais perment le chevauchement
//char tab[10] = "abcdefghi";
//memmove(tab + 2, tab, 5);
// tab devient : "ababcdehi"
//src = tab → "abcde"
//dest = tab + 2 → "cdefg..."
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest > src)// A supprimer
//	if (dest < src)//si // On copie 5 char à partir de tab[2] ("cdefg") vers tab[0]
		return (ft_memcpy(dest, src, n));
	else if (dest == src /*|| n == 0*/)//si pointe sur la même adresse
		return (dest);
	size_t	i = ft_strlen((char *)src) - 1;// A supprimer
//	size_t	i = n
	while (i >= 0)// A supprimer
//	while (i > 0)
	{
		i--; //en 1er (inverser avec ligne suivante)
		((char *)dest)[i] = ((char *)src)[i];
	}
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1] = "";
	char	*ret = NULL;

	char	*tmp = ft_strchr(buff, '\n');
	while (!tmp)
	{
		if (!str_append_str(&ret, buff))
			return (NULL);
		int	read_ret = read(fd, buff, BUFFER_SIZE);
		if (read_ret == -1)
			return (NULL);
//		if (read_ret == 0)// AJOUTÉ: gestion fin de fichier
//            break;
		buff[read_ret] = 0;
//		tmp = ft_strchr(buff, '\n');
	}
//	if (tmp)
//	{
		if (!str_append_mem(&ret, buff, tmp - buff + 1))
		{
			free(ret);
			return (NULL);
		}
//		ft_memmove(buff, tmp + 1, ft_strlen(tmp + 1) + 1);
//	}
//	else
//	{
//		buff[0] = '\0';
//		if (!ret || !*ret)
//		{
//			free(ret);
//			return (NULL);
//		}
//	}
	return (ret);
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
}*/
/************************************************************ */
