/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:19:38 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/19 23:21:26 by abouhaga         ###   ########.fr       */
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
				printf("minishell: syntax error near unexpected token `newline'\n");
			else if (ft_strlen(lines[i + 1]) > 1)
				printf("minishell: syntax error near unexpected token `%c%c'\n", lines[i + 1][0], lines[i + 1][0]);
			else
				printf("minishell: syntax error near unexpected token `%c'\n", lines[i + 1][0]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_quoted(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\"')
		{
			skip_quote(arg, &i, '\"');
			if (arg[i - 1] != '\"')
				return (0);
		}
		else if (arg[i] == '\'')
		{
			skip_quote(arg, &i, '\'');
			if (arg[i - 1] != '\'')
				return (0);
		}
		else
			i++;
	}
	return (1);
}

int	ft_syntax_error(char **lines, char *token)
{
	int	i;

	i = 0;
	if (!ft_strcmp(lines[0], "|"))
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	while (token[i])
	{
		if (token[i] == '|' && token[i + 1] == '|')
		{
			printf("minishell: syntax error near unexpected token `%c'\n", lines[i][0]);
			return (1);
		}
		if (token[i] == 'E')
		{
			printf("minishell: syntax error near unexpected token `%c%c'\n", lines[i][0], lines[i][0]);
			return (1);
		}
		if (!is_quoted(lines[i]))
		{
			printf("minishell: unclosed quotes\n");
			return (1);
		}
		i++;
	}
	if (!ft_strcmp(lines[i - 1], "|"))
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}
