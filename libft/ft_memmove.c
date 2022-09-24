/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 10:49:32 by midfath           #+#    #+#             */
/*   Updated: 2021/11/18 14:29:20 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int	i;

	i = (int)len - 1;
	if (!src && !dst)
		return (NULL);
	if (dst > src)
	{
		while (i >= 0)
		{	
			*(char *)(dst + i) = *(char *)(src + i);
			i--;
		}
	}
	else
		return (ft_memcpy(dst, src, len));
	return ((char *)dst);
}

/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char dst[] = "hello World";
	memmove(dst, dst + 2, 3);
	printf("%s", dst);
	return (0);
}*/