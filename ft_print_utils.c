
#include "ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (ft_putstr("(null)"));
	while (s[i])
	{
		ft_putchar(s[i]);
		i++;
	}
	return (i);
}

int	ft_putnbr(int n)    // ai
{
	int	len;

	len = 0;
	if (n == -2147483648)
		return (ft_putstr("-2147483648"));
	if (n < 0)
	{
		len += ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
		len += ft_putnbr(n / 10);
	len += ft_putchar((n % 10 + '0'));
	return (len);
}

int	ft_putunsigned(unsigned int n)
{
	int	len;

	len = 0;
	if (n >= 10)
	{
		len += ft_putunsigned(n / 10);
	}
	len += ft_putchar((n % 10) + '0');
	return (len);
}

int	upper_hex(unsigned long long n)
{
	char	*hex;
	int		len;

	hex = "0123456789ABCDEF";
	len = 0;
	if (n >= 16)
		len += upper_hex(n / 16);
	len += ft_putchar(hex[n % 16]);
	return (len);
}

int	lower_hex(unsigned long long n)
{
	char	*hex;
	int		len;

	hex = "0123456789abcdef";
	len = 0;
	if (n >= 16)
		len += lower_hex(n / 16);
	len += ft_putchar(hex[n % 16]);
	return (len);
}

int	adresptr(void *ptr)
{
	int	len;

	len = 0;
	if (ptr == NULL)
    {
        return (ft_putstr("(nil)"));
    }
	
	len += ft_putstr("0x");
	len += (lower_hex((unsigned long long)ptr));
	return (len);
}
