/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:19:38 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/27 22:48:29 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_check_redir_filename(char **lines, char *tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i] != '|' && tokens[i] != 'S' && tokens[i + 1] != 'S')
		{
			if (!lines[i + 1])
				ft_fprintf(2, "minishell: syntax error \
					near unexpected token `newline'\n", NULL);
			else if (ft_strlen(lines[i + 1]) > 1)
				ft_fprintf(2, "minishell: syntax error near \
				unexpected token `%c%c'\n", lines[i + 1][0], lines[i + 1][0]);
			else
				ft_fprintf(2, "minishell: syntax error \
					near unexpected token `%c'\n", lines[i + 1][0]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_quoted(char *str)
{
	int		i;
	char	quote_type;

	i = -1;
	quote_type = '\0';
	while (str[++i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			if (!quote_type)
				quote_type = str[i];
			else if (str[i] == quote_type)
				quote_type = '\0';
		}
	}
	return (quote_type == '\0');
}

int	ft_syntax_error(char **lines, char *token)
{
	int	i;

	i = 0;
	if (!(*lines))
		return (0);
	if (!ft_strcmp(lines[0], "|"))
		return (ft_fprintf(2, "minishell: syntax \
		error near unexpected token `|'\n", NULL));
	while (token[i])
	{
		if (token[i] == '|' && token[i + 1] == '|')
			return (ft_fprintf(2, "minishell: syntax \
			error near unexpected token `%c'\n", lines[i][0]));
		if (token[i] == 'E')
			return (ft_fprintf(2, "minishell: syntax \
			error near unexpected token `%c%c'\n", lines[i][0], lines[i][0]));
		if (!is_quoted(lines[i]))
			return (ft_fprintf(2, "minishell: unclosed quotes\n", NULL));
		i++;
	}
	if (!ft_strcmp(lines[i - 1], "|"))
		return (ft_fprintf(2, "minishell: syntax error \
		near unexpected token `|'\n", NULL));
	return (0);
}
