/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:21:05 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/29 03:26:42 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_add_back_cmd(t_cmds **cmds, t_cmds *new)
{
	t_cmds	*ptr;

	ptr = *cmds;
	if (!ptr)
		*cmds = new;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}

t_cmds	*ft_fillup_struct(t_data *data)
{
	int		i;
	int		last_io[2];
	int		sync;
	t_cmds	*new_cmd;
	t_cmds	*head_cmd;

	i = 0;
	sync = 0;
	head_cmd = 0;
	while (data->s_tokens[i])
	{
		new_cmd = (t_cmds *)malloc(sizeof(t_cmds));
		new_cmd->is_exec = setup_last_io(last_io, data->s_tokens[i], data, i);
		new_cmd->in = last_io[0];
		new_cmd->out = last_io[1];
		new_cmd->args = ft_fill_args(data->lines, data->s_tokens[i], &sync);
		new_cmd->path = get_cmd_path(new_cmd);
		new_cmd->next = NULL;
		ft_add_back_cmd(&head_cmd, new_cmd);
		sync++;
		i++;
	}
	return (head_cmd);
}

char	*unquote_arg(char *str)
{
	int		i;
	int		j;
	char	quote;
	char	*unquoted;

	i = -1;
	j = 0;
	unquoted = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i++];
			while (str[i] != quote)
				unquoted[j++] = str[i++];
			quote = '\0';
			continue ;
		}
		unquoted[j++] = str[i];
	}
	unquoted[j] = '\0';
	unquoted = ft_realloc(unquoted, ft_strlen(unquoted) + 1,
			ft_strlen(unquoted) + 1);
	return (unquoted);
}

t_cmds	*ft_parser(char *line)
{
	int		i;
	t_data	data;
	t_cmds	*cmds;

	data.lines = ft_lexer(line, " \t\r\v\f\n");
	data.tokens = ft_tokenize(data.lines);
	if (ft_syntax_error(data.lines, data.tokens))
		return (NULL);
	if (ft_check_redir_filename(data.lines, data.tokens))
		return (NULL);
	i = -1;
	while (data.lines[++i])
		if (ft_indexof(data.lines[i], '$') == -1)
			data.lines[i] = unquote_arg(data.lines[i]);
	check_expand(&data);
	data.s_tokens = ft_split(data.tokens, '|');
	fill_here_fds(&data);
	fill_infiles(&data);
	fill_outfiles(&data);
	i = -1;
	while (data.lines[++i])
		data.lines[i] = unquote_arg(data.lines[i]);
	cmds = ft_fillup_struct(&data);
	return (cmds);
}
// /* free all addresses not useful anymore */
