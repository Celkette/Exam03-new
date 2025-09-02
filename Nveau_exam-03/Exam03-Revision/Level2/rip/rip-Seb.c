#include <unistd.h>
#include <stdio.h>

void	print(char *src, int len, char *mask)
{
	for (int i = 0; i < len; i++)
	{
		if (mask[i])
			write(1, "_", 1);
		else
			write(1, &src[i], 1);
	}
	write(1, "\n", 1);
}

static int	init_struct(t_data *data, char *line)
{
	if (
	data->open = ;
	data->close = ;
	data->len = ;
	data->start = line;
	data->last = NULL;
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2 || !av[1])
		return (1);
	if (init_struct(&data, av[1]) != 0)
		return (1);
	return (0);
}

