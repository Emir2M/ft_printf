/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirhyil <emirhyil@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/23 16:13:10 by emirhyil          #+#    #+#             */
/*   Updated: 2026/09/23 17:27:25 by emirhyil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	upper_hex(unsigned int n)
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

int	lower_hex(unsigned int n)
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
