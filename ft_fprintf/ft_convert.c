/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 00:26:24 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/27 00:38:22 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int	ft_putnbr_base_unsigned(int fd, unsigned int nbr, char *base)
{
	size_t	result;
	size_t	bs;

	bs = ft_strlen(base);
	result = 0;
	if (nbr >= bs)
	{
		result += ft_putnbr_base_unsigned(fd, (nbr / bs), base);
		return (ft_fputchar(fd, base[(nbr % bs)]) + result);
	}
	else
		return (ft_fputchar(fd, base[nbr]));
}

int	ft_putnbr_base(int fd, int nbr, char *base)
{
	unsigned int	nbr_p;
	size_t			result;
	size_t			bs;

	nbr_p = (unsigned int)nbr;
	bs = ft_strlen(base);
	result = 0;
	if (nbr < 0)
	{
		if (!ft_strncmp(base, DECB, bs))
		{
			nbr_p = nbr * (-1);
			result += ft_fputchar(fd, '-');
		}
		if (nbr_p >= bs)
			result += ft_putnbr_base(fd, (nbr_p / bs), base);
		return (ft_fputchar(fd, base[nbr_p % bs]) + result);
	}
	else if (nbr_p >= bs)
	{
		result += ft_putnbr_base(fd, (nbr_p / bs), base);
		return (ft_fputchar(fd, base[(nbr_p % bs)]) + result);
	}
	else
		return (ft_fputchar(fd, base[nbr_p]));
}

int	ft_putnbr_adrs(int fd, unsigned long long nbr, char *base)
{
	size_t	result;
	size_t	bs;

	bs = ft_strlen(base);
	result = 0;
	if (nbr >= bs)
	{
		result += ft_putnbr_adrs(fd, (nbr / bs), base);
		return (ft_fputchar(fd, base[(nbr % bs)]) + result);
	}
	else
		return (ft_fputchar(fd, base[nbr]));
}

int	ft_printf_adrs(int fd, void *str)
{
	int	s;

	s = ft_fputstr(fd, "0x");
	return (ft_putnbr_adrs(fd, (long long)str, LHEXB) + s);
}
