/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 18:32:39 by midfath           #+#    #+#             */
/*   Updated: 2021/11/14 15:12:17 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*p;
	size_t		i;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen (s))
	{
		p = (char *)malloc(sizeof(char) * 1);
		*p = '\0';
		return (p);
	}
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	p = (char *)malloc(sizeof(char) * len + 1);
	if (!p)
		return (NULL);
	while (s[start] && i < len)
	{
		p[i] = ((char *)s)[start];
		start++;
		i++;
	}
	p[i] = '\0';
	return (p);
}
