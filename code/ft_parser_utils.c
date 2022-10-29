/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:48:47 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/29 17:09:31 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	check_expand(t_data	*data)
{
	int	i;

	i = -1;
	while (data->lines[++i])
	{
		if (data->lines[i][0] == '$' && data->lines[i][1] == '?')
			data->lines[i] = expand(data->lines[i]);
		else if (ft_strchr(data->lines[i], '$') && data->tokens[i - 1] != 'H')
			data->lines[i] = expand(data->lines[i]);
	}
}

int	ft_strptr(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		i++;
	return (i);
}

void	fill_here_fds(t_data *data)
{
	int		i;
	int		sync;

	i = -1;
	sync = 0;
	data->here_fds = (int **)malloc(sizeof(int *) * \
		(ft_strptr(data->s_tokens)));
	while (data->s_tokens[++i])
	{
		data->here_fds[i] = ft_open_hdocs(data->lines,
				data->s_tokens[i], &sync);
		sync++;
	}
}

void	fill_infiles(t_data *data)
{
	int	i;
	int	sync;

	i = -1;
	sync = 0;
	data->infiles = (int **)malloc(sizeof(int *) * (ft_strptr(data->s_tokens)));
	while (data->s_tokens[++i])
	{
		data->infiles[i] = ft_open_infiles(data->lines, \
		data->s_tokens[i], &sync);
		sync++;
	}
}

void	fill_outfiles(t_data *data)
{
	int	i;
	int	sync;

	i = -1;
	sync = 0;
	data->outfiles = (int **)malloc(sizeof(int *) * \
	(ft_strptr(data->s_tokens)));
	while (data->s_tokens[++i])
	{
		data->outfiles[i] = ft_open_outfiles(data->lines, data->s_tokens[i],
				&sync);
		sync++;
	}
}
