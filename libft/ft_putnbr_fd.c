/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 15:11:58 by midfath           #+#    #+#             */
/*   Updated: 2021/11/18 14:34:56 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	m;

	if (n < 0)
	{
		n *= -1;
		ft_putchar_fd('-', fd);
	}
	m = (unsigned int)n;
	if (m <= 9)
		ft_putchar_fd((m + '0'), fd);
	else
	{
		ft_putnbr_fd(m / 10, fd);
		ft_putchar_fd(m % 10 + '0', fd);
	}
}

/*#include <fcntl.h>

int	main(void)
{
	int	fd;

	fd = open("./test.txt", O_RDWR | O_CREAT);
	ft_putnbr_fd(1337, fd);
	return (0);
}*/