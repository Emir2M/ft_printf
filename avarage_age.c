/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avarage_age.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirhyil <emirhyil@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/23 16:14:11 by emirhyil          #+#    #+#             */
/*   Updated: 2026/09/23 16:22:17 by emirhyil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

float	avarage(int n, ...)
{
	va_list	ap;
	int		total;
	int		i;

	va_start(ap, n);
	total = 0;
	i = 0;
	while (i < n)
	{
		total += va_arg(ap, int);
		i++;
	}
	return (total / n);
}

int	main(void)
{
	float avarage_age;

	avarage_age = avarage(3, 21, 28, 45);
	printf("kişilerin ortalama yaşi : %f\n", avarage_age);
}