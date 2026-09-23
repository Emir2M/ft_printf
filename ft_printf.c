#include "ft_printf.h"

int format(char c)
{
	if(c == 'c')
		ft_putchar(va_arg(ap, char));
	if(c == 's')
		ft_putstr(va_arg(ap, char *));
	if(c == 'p')
		adresptr(va_arg(ap, void *));
	if(c == 'd' || c == 'i')
		ft_putnbr(va_arg(ap, int));
	if(c == 'u')
		ft_putunsigned(va_arg(ap, unsigned int));
	if(c == 'x')
		lower_hex(va_arg(ap, char *));
	if(c == 'X')
		upper_hex(va_arg(ap, char *));
	else(c == '%')
		ft_putchar(" ");
}


int ft_printf(const char *string, ...)
{
	va_list ap;
	va_start(ap, string);

	int i = 0;
	while(string[i]!='\0')
	{
		if(string[i]=='%')
			format(string[i+1]);
		i++;
	}
}