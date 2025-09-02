#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

int	ft_pourcent(void)
{
	write(1, "%", 1);
	return (1);
}
int ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}
int ft_str(char *s)
{
	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	int i = 0;
	while (s[i]){
		ft_putchar(s[i]);
		i++;
	}
	return i;
}
int ft_putnbr(int n)
{
	int count = 0;
	if (n == INT_MIN)
	{
		ft_putchar('-');
		ft_str("2147483647");
		return 11;
	}
	if (n < 0)
	{
		count += ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
		count += ft_putnbr(n / 10);
	count += ft_putchar(n % 10 + '0');
	return count;
}
int	ft_hex(unsigned int n)
{
	int count = 0;
	char *hex = "0123456789abcdef";
	if (n >= 16)
		count += ft_hex(n / 16);
	count += ft_putchar(hex[n % 16]);
	return count;
}
int ft_type(const char f, va_list arg)
{
	int count = 0;
	if (f == '%')
		count += ft_pourcent();
	else if (f == 's')
		count += ft_str(va_arg(arg, char *)); 
	else if (f == 'd')
		count += ft_putnbr(va_arg(arg, int));
	else if (f == 'x')
		count += ft_hex(va_arg(arg, unsigned int));
	return count;
}

int	ft_printf(const char *f, ...)
{
	int count = 0, i = 0;
	va_list arg;

	if (!f || f[0] == '\0')
		return 0;
	va_start(arg, f);
	while (f[i])
	{
		if (f[i] == '%')
		{
			count += ft_type(f[i + 1], arg);
			i++;
		}
		else
			count += ft_putchar(f[i]);
		i++;
	}
	va_end(arg);
	return count;
}
int main(void)
{
	int c = 0;
	c = printf("%s %d %x %% \n", "test a moi meme", -123, 1234);
	printf("c %d \n", c);
	c = ft_printf("%s %d %x %% \n", "test a moi meme", -123, 1234);
	printf("c %d \n", c);
	return (0);
}
