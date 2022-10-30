/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 00:25:26 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/29 15:21:04 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

static int	ft_write_sign(int fd, char c, va_list arg)
{
	if (c == 'c')
		return (ft_fputchar(fd, va_arg(arg, int)));
	if (c == 's')
		return (ft_fputstr(fd, va_arg(arg, char *)));
	if (c == 'p')
		return (ft_printf_adrs(fd, va_arg(arg, void *)));
	if (c == 'd' || c == 'i')
		return (ft_putnbr_base(fd, va_arg(arg, int), DECB));
	if (c == 'u')
		return (ft_putnbr_base_unsigned(fd, (va_arg(arg, unsigned int)), DECB));
	if (c == 'x')
		return (ft_putnbr_base(fd, va_arg(arg, int), LHEXB));
	if (c == 'X')
		return (ft_putnbr_base(fd, va_arg(arg, int), UHEXB));
	if (c == '%')
		return (write(fd, &c, 1));
	return (0);
}

int	ft_fprintf(int fd, const char *arg, ...)
{
	va_list	str;
	size_t	i;
	int		save;

	va_start(str, arg);
	i = 0;
	save = 0;
	while (arg[i])
	{
		if (arg[i] == '%')
			save += ft_write_sign(fd, arg[++i], str);
		else
			save += write(fd, &arg[i], 1);
		i++;
	}
	va_end(str);
	return (save);
}
