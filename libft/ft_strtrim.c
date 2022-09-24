/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:34:09 by midfath           #+#    #+#             */
/*   Updated: 2021/11/14 17:53:22 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "libft.h"

int	ft_chrstr(char chr, char *s)
{
	int	j;

	j = 0;
	while (s[j])
	{
		if (s[j] == chr)
			return (1);
		j++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int		len;

	if (!s1)
		return (NULL);
	while (*s1 && ft_chrstr(*s1, (char *)set))
		s1++;
	len = ft_strlen(s1);
	while (len && ft_chrstr(s1[len - 1], (char *)set))
		len--;
	return (ft_substr(s1, 0, len));
}
