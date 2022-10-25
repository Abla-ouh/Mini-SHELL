/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:22:08 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/25 02:05:59 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


int	ft_read_stdin(char **lines, int del_idx)
{
	char	*temp;
	int		here_fds[2];
	int		expand_in_hdoc;

	pipe(here_fds);
	expand_in_hdoc = (!ft_strchr(lines[del_idx], '\"') && !ft_strchr(lines[del_idx], '\''));
	lines[del_idx] = unquote_arg(lines[del_idx]); // getting the limiter unquoted
	while(1)
	{
		temp = readline("> ");
		if (!temp || !ft_strcmp(temp, lines[del_idx]))
			break ;
		if (expand_in_hdoc)
			temp = expand(temp);
		write(here_fds[STDOUT_FILENO], temp, ft_strlen(temp));
		write(here_fds[STDOUT_FILENO], "\n", 1);
		free(temp);
	}
	if (temp)
		free(temp);
	close(here_fds[STDOUT_FILENO]);
	return (here_fds[STDIN_FILENO]);
}

int	find_op(char *tokens, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokens[i])
	{
		if (tokens[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	*ft_open_hdocs(char **lines, char *tokens, int *sync_lines)
{
	int	*here_fds;
	int	here_num;
	int	i;
	int	j;

	here_num = find_op(tokens, 'H');
	if (!here_num)
	{
		*sync_lines += ft_strlen(tokens);
		return (NULL);
	}
	here_fds = malloc(sizeof(int) * (here_num));
	i = -1;
	j = 0;
	while (++i < here_num)
	{
		while (tokens[j] && tokens[j] != 'H')
		{
			(*sync_lines)++;
			j++;
		}
		here_fds[i] = ft_read_stdin(lines, ++(*sync_lines));
		j++;
	}
	*sync_lines += ft_strlen(&tokens[j]);
	return (here_fds);
}
