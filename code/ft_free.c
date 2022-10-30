/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 22:08:08 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/30 14:43:00 by abouhaga         ###   ########.fr       */
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

// void	ft_free_cmds(t_cmds *cmds)
// {
// 	int	i;

// 	if (cmds == 0x0)
// 		return ;
// 	i = 0;
// 	while (cmds->args[i])
// 	{
// 		free(cmds->args[i]);
// 		i++;
// 	}
// 	free(cmds->args);
// 	free(cmds);
// }

// void	ft_free_all(t_cmds *cmds)
// {
// 	t_cmds	*tmp;

// 	if (cmds == 0x0)
// 		return ;
// 	while (cmds)
// 	{
// 		tmp = cmds->next;
// 		ft_free_cmds(cmds);
// 		cmds = tmp;
// 	}
// }
