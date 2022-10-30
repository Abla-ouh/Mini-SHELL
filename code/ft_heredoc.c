/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:22:08 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/30 06:55:43 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	sig_heredoc(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, &sig_handler_heredoc);
}

static void	sig(void)
{
	signal(SIGINT, &handler);
	dup2(g_glob.infd, STDIN_FILENO);
}

int	ft_read_stdin(char **lines, int del_idx)
{
	char	*temp;
	int		here_fds[2];
	int		expand_in_hdoc;

	pipe(here_fds);
	expand_in_hdoc = (!ft_strchr(lines[del_idx], '\"')
			&& !ft_strchr(lines[del_idx], '\''));
	lines[del_idx] = unquote_arg(lines[del_idx]);
	sig_heredoc();
	while (1)
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
	sig();
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

int	*ft_open_hdocs(char **lines, char *tokens, int *sync)
{
	int	*here_fds;
	int	i;
	int	j;

	if (!find_op(tokens, 'H'))
	{
		*sync += ft_strlen(tokens);
		return (NULL);
	}
	here_fds = malloc(sizeof(int) * (find_op(tokens, 'H')));
	i = -1;
	j = 0;
	while (++i < find_op(tokens, 'H'))
	{
		while (tokens[j] && tokens[j] != 'H')
		{
			(*sync)++;
			j++;
		}
		here_fds[i] = ft_read_stdin(lines, ++(*sync));
		j++;
	}
	*sync += ft_strlen(&tokens[j]);
	return (here_fds);
}
