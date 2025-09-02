#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

int ft_scanf(const char *format, ...)
{
	char	buffer[1024];
	char	*bufptr;
	va_list args;
       	int count = 0;
	if (!fgets(buffer, sizeof(buffer), stdin))
		return -1;
	bufptr = buffer;
	va_start(args, format);
	for (const char *p = format; *p; p++)
	{
		if (*p == '%')
		{
			p++;
			if (*p == 'd')
			{
				int *num = va_arg(args, int*);
				int val = 0;
			        int sign = 1;
				while (*bufptr && isspace(*bufptr))
					bufptr++;
				if (*bufptr == '-')
				{
				       	sign = -1;
					bufptr++;
				}
				else if (*bufptr == '+')
					bufptr++;
				if (!isdigit(*bufptr))
				{ 
					va_end(args);
					return count;
				}
				while (isdigit(*bufptr))
					val = val*10 + (*bufptr++ - '0');
				*num = val * sign; count++;
			}
			else if (*p == 's')
			{
				char *str = va_arg(args, char*);
				int i = 0;
				while (isspace(*bufptr))
					bufptr++;
				while (*bufptr && !isspace(*bufptr))
					str[i++] = *bufptr++;
				str[i] = 0; count++;
			}
		}
		else if (*bufptr == *p)
		       	bufptr++;
	}
	va_end(args);
	return count;
}

int main(void) {
	int entier;
	char mot[100];
	printf("Entrez un entier puis un mot : ");
	if (ft_scanf("%d %s", &entier, mot) != 2)
	{
		printf("Erreur de saisie.\n");
		return 1;
	}
	printf("Entier lu : %d\nMot lu    : %s\n", entier, mot);
	return 0;
}
