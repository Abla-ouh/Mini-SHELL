/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:08:45 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/18 00:31:18 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../inc/minishell.h>

int	ft_srch(char *str, char c)
{
    int i;

    i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_getend(char *str,char *set, int end)
{
	while (ft_srch(set, str[end]) && end > 0)
		end--;
	return (end);
}

char	*ft_str_trim(char *s, char *set)
{
	int		end;
	int		i;
	int		j;
	char	*trimmed;
	
	end = 0;
	if (s == NULL || set == NULL)
		return (NULL);
	end = ft_getend(s, set, ft_strlen(s) - 1);
	if (ft_strlen(s) == 0 || end == 0)
		return (ft_calloc(1, 1));
	i = 0;
	while (ft_srch(set, s[i]) && s[i])
		i++;
	trimmed = ft_calloc(end - i + 2, sizeof(char));
	if (trimmed == NULL)
		return (NULL);
	j = 0;
	while (i <= end && s[i])
	{
		trimmed[j] = s[i];
		i++;
		j++;
	}
	return (trimmed);
}