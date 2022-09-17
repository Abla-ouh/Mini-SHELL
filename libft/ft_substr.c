/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:57:02 by abouhaga          #+#    #+#             */
/*   Updated: 2022/07/05 20:57:04 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	char			*p;

	i = 0;
	if (s == 0)
		return (NULL);
	if (ft_strlen(s) < len)
		len = ft_strlen(s) - start;
	if (start > ft_strlen(s))
	{
		p = (char *)malloc(sizeof(char ) * 1);
		*p = '\0';
		return (p);
	}
	p = (char *)malloc(sizeof(char) * len + 1);
	if (!p)
		return (NULL);
	while (s[start + i] && i < len)
	{
		p[i] = s[start + i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
