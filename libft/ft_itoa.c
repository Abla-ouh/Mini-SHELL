/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 13:00:47 by midfath           #+#    #+#             */
/*   Updated: 2021/11/11 16:02:22 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_digits(int n)
{
	int				digit;
	unsigned int	m;

	digit = 1;
	if (n < 0)
	{
		m = -n;
		digit++;
	}
	else
		m = n;
	while (m >= 10)
	{
		m /= 10;
		digit++;
	}
	return (digit);
}

static char	*ft_fill(char *p, int n, unsigned int m)
{
	while (m)
	{
		p[--n] = (m % 10) + '0';
		m /= 10;
	}
	return (p);
}

char	*ft_itoa(int n)
{
	char			*p;
	int				digit;
	unsigned int	m;

	digit = ft_digits(n);
	p = (char *)malloc(sizeof(char) * (digit + 1));
	if (!p)
		return (NULL);
	if (n < 0)
	{
		p[0] = '-';
		m = -n;
	}
	else
		m = n;
	p[digit] = '\0';
	if (n == 0)
		p[0] = '0';
	else
		p = ft_fill(p, digit, m);
	return (p);
}
