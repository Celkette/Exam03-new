#include "power_set.h"

static int	target;
static int	*num;
static int	n;
static int	*sub;
static int	sub_size;

void	bt(int start, int sum)
{
	if (sum == target)
	{
		if (sub_size == 0)
			printf("\n");
		else
		{
			printf("%d", sub[0]);
			for (int i = 1; i < sub_size; i++)
				printf(" %d", sub[i]);
			printf("\n");
		}
	}
	for (int i = start; i < n; i++)
	{
		sub[sub_size++] = num[i];
		bt(i + 1, sum + num[i]);
		sub_size--;
	}
}
int	main(int ac, char **av)
{
	if (ac < 2)
		return (0);
	target = atoi(av[1]);
	n = ac - 2;
	num = malloc(sizeof(int) * n);
	if (!num)
		//exit(1);//pas standard
		return (1);
	sub = malloc(sizeof(int) * n);
	if (!sub)
		exit(1);
	for (int i = 0; i < n; i++)
		num[i] = atoi(av[i + 2]);
	sub_size = 0;
	bt(0, 0);
	free(num);
	free(sub);
	return (0);
}
