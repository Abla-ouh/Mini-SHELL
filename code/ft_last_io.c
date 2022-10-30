/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_last_io.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:27:07 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/30 16:33:46 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_exec_in(t_data *data, int cmd_idx, int last_in, int *last_io)
{
	int	i;

	i = 0;
	while (i < last_in)
	{
		if (data->infiles[cmd_idx][i] < 0)
		{
			last_io[0] = data->infiles[cmd_idx][i];
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_exec_out(t_data *data, int cmd_idx, int last_out, int *last_io)
{
	int	i;

	i = 0;
	while (i < last_out)
	{
		if (data->outfiles[cmd_idx][i] < 0)
		{
			last_io[1] = data->outfiles[cmd_idx][i];
			return (0);
		}
		i++;
	}
	return (1);
}

int	setup_last_io(int *last_io, char *token, t_data *data, int cmd_idx)
{
	int	last_out;
	int	_exec;

	last_out = find_op(token, '>');
	last_out += find_op(token, 'A');
	if (!check_exec_in(data, cmd_idx, find_op(token, '<'), last_io)
		&& !check_exec_out(data, cmd_idx, last_out, last_io))
		return (0);
	if (find_op(token, '<') || find_op(token, 'H'))
	{
		if (ft_strrchr(token, 'H') > ft_strrchr(token, '<'))
			last_io[0] = data->here_fds[cmd_idx][find_op(token, 'H') - 1];
		else
			last_io[0] = data->infiles[cmd_idx][find_op(token, '<') - 1];
	}
	else
		last_io[0] = 0;
	if (last_out)
		last_io[1] = data->outfiles[cmd_idx][last_out - 1];
	else
		last_io[1] = 1;
	_exec = 1;
	return (_exec);
}
