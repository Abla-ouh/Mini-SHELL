/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:56:51 by abouhaga          #+#    #+#             */
/*   Updated: 2022/07/05 20:56:53 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*p;

	i = 0;
	p = (char *)s;
	while (p[i])
		i++;
	while (i >= 0)
	{
		if ((char)c == p[i])
		{
			return (&p[i]);
		}
		i--;
	}
	return (NULL);
}
