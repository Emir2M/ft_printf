/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirhyil <emirhyil@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/23 16:12:29 by emirhyil          #+#    #+#             */
/*   Updated: 2026/09/25 14:52:30 by emirhyil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	format(va_list ap, const char c)
{
	if (c == 'c')
		return ((ft_putchar(va_arg(ap, int))));
	if (c == 's')
		return ((ft_putstr(va_arg(ap, char *))));
	if (c == 'p')
		return ((adresptr(va_arg(ap, void *))));
	if (c == 'd' || c == 'i')
		return ((ft_putnbr(va_arg(ap, int))));
	if (c == 'u')
		return ((ft_putunsigned(va_arg(ap, unsigned int))));
	if (c == 'x')
		return ((lower_hex(va_arg(ap, unsigned int))));
	if (c == 'X')
		return ((upper_hex(va_arg(ap, unsigned int))));
	if (c == '%')
		return ((ft_putchar('%')));
	return (0);
}

int	ft_printf(const char *string, ...)
{
	va_list	ap;
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (!string)
		return (-1);
	va_start(ap, string);
	while (string[i] != '\0')
	{
		if (string[i] == '%')
		{
			i++;
			len += format(ap, string[i]);
		}
		else
			len += ft_putchar(string[i]);
		i++;
	}
	va_end(ap);
	return (len);
}
