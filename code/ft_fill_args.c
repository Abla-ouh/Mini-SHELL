/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:29:36 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/26 11:28:19 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_seperator_char(char c)
{
	return (c != ' '
		&& c != '<'
		&& c != '>'
		&& c != '|'
		&& c != '\t'
		&& c != '\0');
}

void	skip_quote_len(char *trim_line, int i, int *len, char q)
{
	(*len)++;
	while (trim_line[i + (*len)]
		&& trim_line[i + (*len)] != q)
		(*len)++;
	if (trim_line[i + (*len)] == q)
		(*len)++;
}

int	args_to_alloc(char *tokens)
{
	int	i;
	int	s;

	i = 0;
	s = 0;
	while (tokens[i])
	{
		if (tokens[i] == 'S' && (i == 0 || tokens[i - 1] == 'S'))
			s++;
		i++;
	}
	return (s);
}

char	**ft_fill_args(char **lines, char *tokens, int *sync)
{
	int		i;
	int		j;
	char	**args;

	i = -1;
	j = 0;
	args = (char **)malloc(sizeof(char **) * (args_to_alloc(tokens) + 1));
	if (!args)
		return (NULL);
	while (tokens[++i])
	{
		if (tokens[i] == 'S' && (i == 0 || tokens[i - 1] == 'S'))
		{
			args[j] = ft_strdup(lines[*sync]);
			j++;
		}
		(*sync)++;
	}
	args[j] = NULL;
	while (tokens[i++])
		(*sync)++;
	return (args);
}
