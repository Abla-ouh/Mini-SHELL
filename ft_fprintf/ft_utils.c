/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 00:25:52 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/27 00:25:54 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int	ft_fputchar(int fd, char c)
{
	return (write(fd, &c, 1));
}

int	ft_fputstr(int fd, char *str)
{
	size_t	i;

	if (!str)
		return (write(fd, "(null)", 6));
	i = ft_strlen(str);
	return (write(fd, str, i));
}
