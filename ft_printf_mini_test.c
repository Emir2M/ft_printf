/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_mini_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirhyil <emirhyil@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/23 16:29:36 by emirhyil          #+#    #+#             */
/*   Updated: 2026/09/23 16:55:32 by emirhyil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	format(va_list ap, const char c)
{
	if (c == 'c')
		return (va_arg(ap, int));
}

int	ft_printf(const char *string, ...)
{
	va_list	ap;
	int		i;
	int		len;

	i = 0;
	len = 0;
	va_start(ap, string);
	while (string[i] != '\0')
	{
		if (string[i] == '%')
		{
			i++;
			if (!string)
				return (0);
			len += format(ap, string[i]);
		}
		else
			len += ft_putchar(string[i]);
		i++;
	}
	return (len);
}

int	main(void)
{
	ft_printf("merhaba %c\n merhaba", 'x');
}
