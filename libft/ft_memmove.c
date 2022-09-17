/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:55:07 by abouhaga          #+#    #+#             */
/*   Updated: 2022/07/05 20:55:09 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (!d && !s)
		return (0);
	if (d < s)
	{
		while (len--)
		{
			*d++ = *s++;
		}
		return (dst);
	}
	else
	{
		s += len - 1;
		d += len - 1;
		while (len--)
		{
			*d-- = *s--;
		}
	}
	return (dst);
}
