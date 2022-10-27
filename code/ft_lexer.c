/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:10:10 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/26 10:48:55 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	valid_word(char *str_trim, int *i)
{
	if (str_trim[*i] != ' ' && str_trim[*i] != '\t' && str_trim[*i] != '\0')
	{
		if (str_trim[*i] == '<')
			return (find_until_not(str_trim, i, '<'));
		else if (str_trim[*i] == '>')
			return (find_until_not(str_trim, i, '>'));
		else if (str_trim[*i] == '|')
			return (find_until_not(str_trim, i, '|'));
		else
			find_string(str_trim, i);
	}
	else
		return (0);
	return (1);
}

int	get_len(char *line, char *set)
{
	int		i;
	int		len;
	char	*str_trim;

	i = 0;
	len = 0;
	str_trim = ft_strtrim(line, set);
	if (!str_trim)
		return (-1);
	while (str_trim[i])
	{
		if (valid_word(str_trim, &i))
			len++;
		else
			i++;
	}
	free(str_trim);
	return (len);
}

char	*fill_arg(char *trim_line, int *i)
{
	int		len;
	int		j;
	char	*arg;

	len = 0;
	if (trim_line[(*i) + len] != ' '
		&& trim_line[(*i) + len] != '\t' && trim_line[(*i) + len] != '\0')
	{
		if (trim_line[(*i) + len] == '<')
			count_until_not(trim_line, *i, &len, '<');
		else if (trim_line[(*i) + len] == '>')
			count_until_not(trim_line, *i, &len, '>');
		else if (trim_line[(*i) + len] == '|')
			count_until_not(trim_line, *i, &len, '|');
		else
			count_string(trim_line, *i, &len);
	}
	arg = (char *)malloc(sizeof(char) * (len + 1));
	j = 0;
	while (len--)
		arg[j++] = trim_line[(*i)++];
	arg[j] = 0;
	return (arg);
}

char	**ft_lexer(char *line, char *set)
{
	int		i;
	int		j;
	int		arr_len;
	char	**strs;
	char	*trim_line;

	i = 0;
	if (!line || !set)
		return (NULL);
	arr_len = get_len(line, set);
	strs = ft_calloc(arr_len + 1, sizeof(char **));
	if (!strs)
		return (NULL);
	trim_line = ft_strtrim(line, set);
	j = 0;
	while (trim_line[i])
	{
		if (trim_line[i] != ' ' && trim_line[i] != '\t' && trim_line[i] != '\0')
			strs[j++] = fill_arg(trim_line, &i);
		else
			i++;
	}
	return (strs);
}
