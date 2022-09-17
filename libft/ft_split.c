/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:55:38 by abouhaga          #+#    #+#             */
/*   Updated: 2022/07/05 20:55:39 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_word(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{	
		if (s[i] && s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			count++;
		i++;
	}
	return (count);
}

static char	**ft_free(char **str, int k)
{
	while (k >= 0)
	{
		free(str[k]);
		k--;
	}
	return (str);
}

static char	**ft_get_word(char **str, char const *s, char c)
{
	int	i;
	int	len_word;
	int	k;

	i = 0;
	k = 0;
	len_word = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			break ;
		while (s[i] != c && s[i] && s[i++])
			len_word++;
		str[k] = (char *)malloc(sizeof (char) * (len_word + 1));
		if (!str[k])
			return (ft_free(str, k - 1));
		k++;
		len_word = 0;
	}
	str[k] = NULL;
	return (str);
}

static char	**ft_fill_str(char **str, char const *s, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (s[k])
	{
		j = 0;
		while (s[k] && s[k] == c)
			k++;
		if (!s[k])
			break ;
		while (s[k] && s[k] != c)
		{
			str[i][j] = s[k];
			k++;
			j++;
		}
		str[i][j] = '\0';
		i++;
	}
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		count;
	char	**str;

	if (!s)
		return (0);
	count = ft_count_word(s, c);
	str = (char **)malloc(sizeof(char *) * (count + 1));
	if (!str)
		return (NULL);
	str = ft_get_word(str, s, c);
	str[count] = 0;
	return (ft_fill_str(str, s, c));
}
// #include <stdio.h>
// int main(void)
// {
// 	char **str;
// 	int i = 0;
// 	str = ft_split("aaaaaaa", 'a');
// 	printf("%p\n", *str);
// 	return (0);
// }