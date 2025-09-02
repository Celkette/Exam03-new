#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


char	*ft_strdup(char *s)
{
    int len = 0;
    while (s[len])
        len++;
    char *dup = malloc(sizeof(char) * (len + 1));
    if (!dup)
        return NULL;
    for (int i = 0; i <= len; i++)
        dup[i] = s[i];
    return (dup);
}
int ft_strlen(char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return i;
}
void	ft_swap(char *s, char *ss)
{
	char tmp = *s;
	*s = *ss;
	*ss = tmp;
}

void	ft_sort(char *s)
{
	for(int x = 0; s[x]; x++)
	{
		for(int y = x + 1; s[y]; y++)
		{
			if(s[x] > s[y])
				ft_swap(&s[x], &s[y]);
		}
	}
}

void	ft_print(char *s, int n)
{
	write(1, s, n);
	write(1, "\n", 1);
}

void	ft_solve(char *s, int start, int n)
{
	if(start == n)
	{
		ft_print(s, n);
		return ;
	}
	for(int x = start; x < n; x++)
	{
		ft_swap(&s[start], &s[x]);
		ft_solve(s, start + 1, n);
		ft_swap(&s[start], &s[x]);
	}
}


int main(int ac, char **av)
{
	(void)ac;//needs to be changed
	char *s = ft_strdup(av[1]);
	int n = ft_strlen(av[1]);
	ft_sort(s);
	ft_solve(s, 0, n);
	free(s);

}
