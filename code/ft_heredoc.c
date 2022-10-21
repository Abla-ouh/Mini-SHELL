/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:22:08 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/19 23:28:12 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_read_stdin(char **lines, int del_idx)
{
	char	*temp;
	int		here_fds[2];

	pipe(here_fds);
	while (1)
	{
		temp = readline("> ");
		if (!temp || !ft_strcmp(temp, lines[del_idx]))
			break ;
		write(here_fds[1], temp, ft_strlen(temp));
		free(temp);
	}
	if (temp) //khrj b delimeter
		free(temp);
	close(here_fds[1]);
	return (here_fds[0]);
}

int	find_op(char *tokens, char c)
{
	int	i;
	int	her;

	i = 0;
	her = 0;
	while (tokens[i])
	{
		if (tokens[i] == c)
			her++;
		i++;
	}
	return (her);
}

int	*ft_open_hdocs(char **lines, char *tokens, int *sync_lines)
{
	int	*here_fds;
	int	here_num;
	int	i;
	int	j;

	here_num = find_op(tokens, 'H');
	i = 0;
	if (!here_num)
	{
		while (tokens[i++])
			(*sync_lines)++;
		return (NULL);
	}
	here_fds = malloc(sizeof(int) * (here_num + 1));
	j = 0;
	while (i < here_num)
	{
		while (tokens[j] && tokens[j] != 'H')
		{
			(*sync_lines)++;
			j++;
		}
		here_fds[i] = ft_read_stdin(lines, ++(*sync_lines));
		i++;
	}
	while (tokens[j++])
		(*sync_lines)++;
	// i = 0;
	// while(i < here_num)
	// {
	// 	j = 0;
	// 	while(j < 2)
	// 	{
	// 		printf("%d  ", here_fds[i][j]);
	// 		j++;
	// 	}
	// 	printf("\n");
	// 	i++;
	// }
	// exit(1);
	return (here_fds);
}
