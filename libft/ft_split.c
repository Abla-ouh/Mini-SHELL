/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:10:05 by midfath           #+#    #+#             */
/*   Updated: 2021/11/18 13:08:49 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_count(char const*s, char c)
{
	int	count;
	int	j;

	count = 0;
	j = 0;
	while (s[j])
	{
		if (s[j] == c)
		j++;
		else
		{
			while (s[j] && s[j] != c)
				j++;
			count++;
		}
	}
	return (count);
}

static void	ft_free(char **ptr, int i)
{
	while (i--)
		free(ptr[i]);
	free (ptr);
}

char	**ft_split(char const *s, char c)
{
	int		l;
	int		j;
	int		start;
	char	**ret;

	if (!s)
		return (NULL);
	ret = (char **)malloc((ft_count(s, c) + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	j = 0;
	l = 0;
	while (l < ft_count(s, c))
	{
		while (s[j] == c)
			j++;
		start = j;
		while (s[j] != c && s[j])
			j++;
		ret[l++] = ft_substr(s, start, j - start);
		if (!ret[l - 1])
			ft_free(ret, l);
	}
	ret[l] = NULL;
	return (ret);
}
