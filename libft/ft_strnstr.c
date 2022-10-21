/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:39:15 by midfath           #+#    #+#             */
/*   Updated: 2021/11/07 18:02:12 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*to_find == '\0')
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (to_find[j] == haystack[i + j] && to_find[j] && i + j < len)
			j++;
		if (i + j > len)
			return (NULL);
		if (!to_find[j])
			return ((char *)haystack + i);
		i++;
	}
	return (0);
}
