/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 22:08:08 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/31 18:42:14 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_2d_char(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	cleanup(t_data *data)
{
	int	i;
	int	max;

	i = 0;
	max = ft_strptr(data->s_tokens);
	while (data->lines[i])
	{
		free(data->lines[i]);
		i++;
	}
	free(data->lines);
	i = 0;
	while (i < max)
	{
		free(data->s_tokens[i]);
		free(data->here_fds[i]);
		free(data->infiles[i]);
		free(data->outfiles[i]);
		i++;
	}
	free(data->s_tokens);
	free(data->here_fds);
	free(data->infiles);
	free(data->outfiles);
}

void	ft_free_all_stuff_and_start_again(t_cmds *shel_l)
{
	t_cmds	*cmds;
	t_cmds	*current_cmds;

	cmds = shel_l;
	while (cmds)
	{
		if (cmds->path)
			free(cmds->path);
		free_2d_char(cmds->args);
		if (cmds->in)
			close(cmds->in);
		if (cmds->out > 1)
			close(cmds->out);
		current_cmds = cmds;
		cmds = cmds->next;
		free(current_cmds);
	}
	ft_arrfreey();
}
