/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_shell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:21:05 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/25 02:18:04 by abouhaga         ###   ########.fr       */
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
	int		is_exec;
	int		sync_lines;
	t_cmds	*new_cmd;
	t_cmds	*head_cmd;

	i = 0;
	sync_lines = 0;
	is_exec = 0;
	head_cmd = 0;
	while (data->splitted_tokens[i])
	{
		new_cmd = (t_cmds *)malloc(sizeof(t_cmds));
		new_cmd->is_exec = setup_last_io(last_io, data->splitted_tokens[i], data, i);
		new_cmd->in = last_io[0];
		new_cmd->out = last_io[1];
		new_cmd->args = ft_fill_args(data->lines, data->splitted_tokens[i], &sync_lines);
		new_cmd->path = get_cmd_path(new_cmd);
		new_cmd->next = NULL;
		ft_add_back_cmd(&head_cmd, new_cmd);
		sync_lines++;
		i++;
	}
	return (head_cmd);
}

int	ft_strptr(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		i++;
	return (i);
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
	unquoted = ft_realloc(unquoted, ft_strlen(unquoted) + 1, ft_strlen(unquoted) + 1);
	return (unquoted);
}

t_cmds	*ft_parser(char *line)
{
	int		i;
	int		sync_lines;
	t_data	data;
	t_cmds	*cmds;
	t_cmds	*tmp;

	data.lines = ft_lexer(line, " \t\r\v\f\n");
	data.tokens = ft_tokenize(data.lines);
	if (ft_syntax_error(data.lines, data.tokens))
		return (NULL);
	if (ft_check_redir_filename(data.lines, data.tokens))
		return (NULL);
	i = -1;
	while (data.lines[++i])
		if (ft_strchr(data.lines[i], '$') && data.tokens[i - 1] != 'H')
			data.lines[i] = expand(data.lines[i]);
	data.splitted_tokens = ft_split(data.tokens, '|');
	data.here_fds = (int **)malloc(sizeof(int *) * (ft_strptr(data.splitted_tokens)));
	i = -1;
	sync_lines = 0;
	while (data.splitted_tokens[++i])
	{
		data.here_fds[i] = ft_open_hdocs(data.lines, data.splitted_tokens[i], &sync_lines);
		sync_lines++;
	}
	data.infiles = (int **)malloc(sizeof(int *) * (ft_strptr(data.splitted_tokens)));
	i = -1;
	sync_lines = 0;
	while (data.splitted_tokens[++i])
	{
		data.infiles[i] = ft_open_infiles(data.lines, data.splitted_tokens[i], &sync_lines);
		sync_lines++;
	}
	data.outfiles = (int **)malloc(sizeof(int *) * (ft_strptr(data.splitted_tokens)));
	i = -1;
	sync_lines = 0;
	while (data.splitted_tokens[++i])
	{
		data.outfiles[i] = ft_open_outfiles(data.lines, data.splitted_tokens[i], &sync_lines);
		sync_lines++;
	}
	i = -1;
	while (data.lines[++i])
		data.lines[i] = unquote_arg(data.lines[i]);
	cmds = ft_fillup_struct(&data);
	i = 0;
	tmp = cmds;
	while (tmp)
	{
		i = 0;
		while (tmp->args[i])
		{
			printf("arg : %s index %d\n", tmp->args[i], i);
			i++;
		}
		printf("\n");
		printf("tmp->in: %d\n", tmp->in);
		printf("tmp->out: %d\n", tmp->out);
		printf("tmp->is_exec: %d\n", tmp->is_exec);
		printf("tmp->path: %s\n", tmp->path);
		printf("-------------------------------------------------------\n");
		tmp = tmp->next;
	}
    /* free all addresses not useful anymore */
	return (cmds);
}
