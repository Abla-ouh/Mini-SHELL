/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:55:44 by abouhaga          #+#    #+#             */
/*   Updated: 2022/07/05 20:55:46 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*p;

	i = 0;
	p = (char *)s;
	while (p[i])
	{
		if (p[i] == (char)c)
			return (&p[i]);
		i++;
	}
	if (p[i] == (char)c)
		return (&p[i]);
	return (0);
}
