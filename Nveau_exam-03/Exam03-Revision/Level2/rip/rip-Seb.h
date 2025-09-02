#ifndef RIP_H
# define RIP_H

#include <unistd.h>
#include <stdio.h>

typedef struct s_data
{
	int	open;
	int	close;
	int	len;
	char	*start;
	char	*last;
}		t_data;

#endif
