/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_shell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:21:05 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/20 22:14:56 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// int	is_double_quoted(char *arg, int *len)
// {
// 	int	i;

// 	i = 0;
// 	while (arg[i])
// 	{
// 		if (arg[i] == '\"')
// 		{
// 			skip_quote_len(arg, i, len ,'\"');
// 			if (arg[i - 1] != '\"')
// 				return (0);
// 		}
// 		else
// 			i++;
// 	}
// 	return (1);
// }

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

int	unquoted_str_len(char *str)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (str[++i])
		if (str[i] != '\'' && str[i] != '\"')
			len++;
	return (len);
}

char	*unquote_arg(char *str)
{
	int		i;
	int		j;
	char	quote;
	char	*unquoted;

	i = -1;
	j = 0;
	unquoted = malloc(sizeof(char) * (unquoted_str_len(str) + 1));
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
	t_data	data;
	t_cmds	*cmds;
	int		i;
	int		sync_lines;

	data.lines = ft_lexer(line, " \t\r\v\f\n");
	data.tokens = ft_tokenize(data.lines);
	if (ft_syntax_error(data.lines, data.tokens))
		return (NULL);
	if (ft_check_redir_filename(data.lines, data.tokens))
		return (NULL);
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
	i = 0;
	while (data.lines[i])
	{
		data.lines[i] = unquote_arg(data.lines[i]);
		i++;
	}
	cmds = ft_fillup_struct(&data);
	i = 0;
	while (cmds)
	{
		i = 0;
		while (cmds->args[i])
		{
			printf("arg : %s index %d\n", cmds->args[i], i);
			i++;
		}
		printf("\n");
		printf("cmds->in: %d\n", cmds->in);
		printf("cmds->out: %d\n", cmds->out);
		printf("cmds->is_exec: %d\n", cmds->is_exec);
		printf("cmds->path: %s\n", cmds->path);
		printf("-------------------------------------------------------\n");
		cmds = cmds->next;
	}
    /* free all addresses not useful anymore */
	return (cmds);
}
