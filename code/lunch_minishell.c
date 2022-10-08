/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lunch_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:21:05 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/07 21:20:47 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../inc/minishell.h>

# define F_NO_SUCH_FILE -2
# define F_PERMISSION_DENIED -3


int is_seperator_char(char c)
{
    return (c != ' ' && c != '<' && c != '>' && c != '|' && c != '\t' && c != '\0');
}

void    skip_quote(char *str_trim, int *i, char q)
{
    (*i)++;
    while (str_trim[*i] && str_trim[*i] != q)
        (*i)++;
    if (str_trim[*i] == q)
        (*i)++;
}

void    find_string(char *str_trim, int *i)
{
    while (is_seperator_char(str_trim[*i]))
    {
        if (str_trim[*i] == '"')
            skip_quote(str_trim, i, '"');
        else if (str_trim[*i] == '\'')
            skip_quote(str_trim, i, '\'');
        else
            (*i)++;
    }
}

int    find_until_not(char *str_trim, int *i, char o)
{
    while (str_trim[*i] == o)
        (*i)++;
    return (1);
}

int valid_word(char *str_trim, int *i)
{
    if (str_trim[*i] != ' ' && str_trim[*i] != '\t' && str_trim[*i] != '\0')
    {
        if (str_trim[*i] == '<')
            return (find_until_not(str_trim, i, '<'));
        else if (str_trim[*i] == '>')
            return (find_until_not(str_trim, i, '>'));
        else if (str_trim[*i] == '|')
            return (find_until_not(str_trim, i, '|'));
        else
            find_string(str_trim, i);        
    }
    else
        return (0);
    return (1);
}

int	get_len(char *line, char *set)
{
	char	*str_trim;
    int     len;
    int     i;

    len = 0;
    i = 0;
	str_trim = ft_str_trim(line, set);
    if(str_trim == NULL)
        return (-1);
    while(str_trim[i])
    {
        // if(ft_strchr(set, str_trim[i]) != NULL)
        //     len++;
        if (valid_word(str_trim, &i))
            len++;
        else
            i++;
    }
	free(str_trim);
    return (len);
}

size_t  word_len(char *str, char *set)
{
	size_t	size;

	size = 0;
	while (*str && ft_strchr(set, *str) == NULL)
	{
		size++;
		str++;
	}
	return (size);
}

void    count_until_not(char *trim_line, int i, int *len, char o)
{
    while (trim_line[i + (*len)] == o)
        (*len)++;
}

void    skip_quote_len(char *trim_line, int i, int *len, char q)
{
    (*len)++;
    while (trim_line[i + (*len)] && trim_line[i + (*len)] != q) //keep iterating until next quote 
        (*len)++;
    if (trim_line[i + (*len)] == q)
        (*len)++;
}

void   count_string(char *trim_line, int i, int *len)
{
    while (is_seperator_char(trim_line[i + (*len)]))
    {
        if (trim_line[i + (*len)] == '"')
            skip_quote_len(trim_line, i, len, '"');
        else if (trim_line[i + (*len)] == '\'')
            skip_quote_len(trim_line, i, len, '\'');
        else
            (*len)++;
    }
}

char *fill_arg(char *trim_line, int *i)
{
    int len;
    int j;
    char *arg;

    len = 0;
    if (trim_line[(*i) + len] != ' ' && trim_line[(*i) + len] != '\t' && trim_line[(*i) + len] != '\0')
    {
        if (trim_line[(*i) + len] == '<')
            count_until_not(trim_line, *i, &len, '<');
        else if (trim_line[(*i) + len] == '>')
            count_until_not(trim_line, *i, &len, '>');
        else if (trim_line[(*i) + len] == '|')
            count_until_not(trim_line, *i, &len, '|');
        else
            count_string(trim_line, *i, &len);
    }
    arg = (char *)malloc(sizeof(char) * (len + 1));
    j = 0;
    while (len--)
        arg[j++] = trim_line[(*i)++];
    arg[j] = 0;
    return (arg);
}

char **ft_lexer(char *line, char *set)
{
	char **strs;
    char *trim_line;
	int	arr_len;
	int i;
	int j;

    i = 0;
	if (line == NULL || set == NULL)
		return (NULL);
	arr_len = get_len(line, set);
    strs = ft_calloc(arr_len + 1, sizeof(char**));
    if (strs == NULL)
        return (NULL);
    trim_line = ft_strtrim(line, set);
    j = 0;
    while (trim_line[i])
    {
        if (trim_line[i] != ' ' && trim_line[i] != '\t' && trim_line[i] != '\0')
            strs[j++] = fill_arg(trim_line, &i);
        else
            i++;
    }
	return (strs);
}

int	is_quoted(char *arg)
{
	int i;

	i = 0;
	while(arg[i])
	{
		if (arg[i] == '\"')
		{
			skip_quote(arg, &i, '\"');
			if (arg[i - 1] != '\"')
				return (0);
		}
		else if (arg[i] == '\'')
		{
			skip_quote(arg, &i, '\'');
			if (arg[i - 1] != '\'')
				return (0);
		}
		else
			i++;
	}
	return (1);
}

int    ft_syntax_error(char **lines, char *token)
{
    int i;

    i = 0;
    if (!ft_strcmp(lines[0], "|"))
    {
        printf("minishell: syntax error near unexpected token `|'\n");
        return (1);
    }
    while(token[i])
    {
        if (token[i] == 'E')
        {
            printf("minishell: syntax error near unexpected token `%c%c'\n", lines[i][0], lines[i][0]);
            return (1);
        }
		if (!is_quoted(lines[i]))
		{
			printf("minishell: unclosed quotes\n");
			return (1);
		}
        i++;
    }
    if (!ft_strcmp(lines[i - 1], "|"))
    {
        printf("minishell: syntax error near unexpected token `|'\n");
        return (1);
    }
    return (0);
}

int	ft_check_redir_filename(char **lines, char *tokens)
{
	int	i;

	i = 0;
	while(tokens[i])
	{
		if (tokens[i] != '|' && tokens[i] != 'S' && tokens[i + 1] != 'S')
		{
			if (!lines[i + 1])
				printf("minishell: syntax error near unexpected token `newline'\n");
			else if (ft_strlen(lines[i + 1]) > 1)
				printf("minishell: syntax error near unexpected token `%c%c'\n", lines[i + 1][0], lines[i + 1][0]);
			else
				printf("minishell: syntax error near unexpected token `%c'\n", lines[i + 1][0]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_read_stdin(char **lines, int del_idx)
{
	char *temp;
	int here_fds[2];

	pipe(here_fds);
	while(1)
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

int find_op(char *tokens, char c)
{
	int i;
	int her;

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
	int j;

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
		while(tokens[j] && tokens[j] != 'H')
		{
			(*sync_lines)++;
			j++;
		}
		here_fds[i] = ft_read_stdin(lines , ++(*sync_lines));
		i++;
	}
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

int	*ft_open_infiles(char **lines, char *tokens, int *sync_lines)
{
	int i;
	int j;
	int	in;
	int *infiles;

	in = find_op(tokens, '<');
	i = 0;
	if(!in)
	{
		while (tokens[i++])
			(*sync_lines)++;
		return (NULL);
	}
	infiles = malloc(sizeof(int) * (in));
	j = 0;
	while (i < in)
	{
		while(tokens[j] && tokens[j] != '<')
		{
			j++;
			(*sync_lines)++;
		}
		if (access(lines[*sync_lines + 1], F_OK) == -1)
		{
			infiles[i] = F_NO_SUCH_FILE;
			printf("minishell: %s: No such file or directory\n", lines[j + 1]);
			i++;
			j++;
			(*sync_lines)++;
			continue ;
		}
		else if (access(lines[*sync_lines + 1], R_OK) == -1)
		{
			infiles[i] = F_PERMISSION_DENIED;
			printf("minishell: %s: Permission denied\n", lines[j + 1]);
			i++;
			j++;
			(*sync_lines)++;
			continue ;
		}	
		infiles[i] = open(lines[*sync_lines + 1], O_RDONLY);
		i++;
	}
	return (infiles);
}

int	*ft_open_outfiles(char **lines, char *tokens, int *sync_lines)
{
	int i;
	int j;
	int	out;
	int *outfiles;

	out = find_op(tokens, '>');
	out += find_op(tokens, 'A');
	i = 0;
	if(!out)
	{
		while (tokens[i++])
			(*sync_lines)++;
		return (NULL);
	}
	j = 0;
	outfiles = malloc(sizeof(int) * (out));
	while (i < out)
	{
		while(tokens[j] && (tokens[j] != '>' && tokens[j] != 'A'))
		{
			j++;
			(*sync_lines)++;
		}
		if (!tokens[j])
			break ;
		if ((tokens[j] == '>' || tokens[j] == 'A') && access(lines[*sync_lines + 1], F_OK) == -1)
		{
			outfiles[i] = open(lines[*sync_lines + 1], O_CREAT | O_WRONLY, 0644);
			i++;
			j++;
			(*sync_lines)++;
			continue ;
		}
		else if (access(lines[*sync_lines + 1], W_OK) == -1)
		{
			outfiles[i] = F_PERMISSION_DENIED;
			printf("minishell: %s: Permission denied\n", lines[j + 1]);
			i++;
			j++;
			(*sync_lines)++;
			continue ;
		}
		if (tokens[j] == '>')
			outfiles[i] = open(lines[*sync_lines + 1], O_TRUNC | O_WRONLY, 0644);
		else
			outfiles[i] = open(lines[*sync_lines + 1], O_APPEND, 0644);
		i++;
	}
	return (outfiles);
}

int check_exec(t_data *data)
{
	int i;

	i = 0;
	while(data->infiles[i] && data->outfiles[i])
	{
		if (data->infiles[i] < 0 || data->outfiles[i] < 0)
			return (0);
	}
	return (1);
}

int	setup_last_io(int *last_io, char *token, t_data *data, int cmd_idx)
{
	int last_in;
	int last_her;
	int last_out;
	int _exec;
	
	last_in = find_op(token, '<');
	last_her = find_op(token, 'H');
	last_out = find_op(token, '>');
	last_out += find_op(token, 'A');
	
	if (!check_exec(data))
	{
		_exec = 0;
		return(_exec);
	}
	if (last_in || last_her)
	{
		if (ft_strrchr(token, 'H') > ft_strrchr(token, '<'))
		{
			last_io[0] = data->here_fds[cmd_idx][last_her - 1];
		}
		else
			last_io[0] = data->infiles[cmd_idx][last_in - 1];
	}
	else
		last_io[0] = 0;
	
	if (last_out)
		last_io[1] = data->outfiles[cmd_idx][last_out - 1];
	else
		last_io[1] = 1;
	_exec = 1;
	return(_exec);
}

int		args_to_alloc(char *tokens)
{
	int i;
	int s;

	i = 0;
	s = 0;
	while (tokens[i])
	{
		if (tokens[i] == 'S' && (i == 0 || tokens[i - 1] == 'S'))
			s++;
		i++;
	}
	return (s);
}

char	**ft_fill_args(char **lines, char *tokens, int *sync_lines)
{
	int i;
	int j;
	int k;
	char	**args;
	
	i = 0;
	j = 0;
	k = 0;

	args = (char **)malloc(sizeof(char**) * (args_to_alloc(tokens) + 1));
	if (!args)
		return(NULL);
	while (tokens[i])
	{
		if (tokens[i] == 'S' && (i == 0 || tokens[i - 1] == 'S'))
		{
			while (tokens[i] == 'S')
			{
				args[j] = ft_strdup(lines[*sync_lines]);
				j++;
				i++;
				(*sync_lines)++;
			}
			break;
		}
		i++;
		(*sync_lines)++;
	}
	args[j] = NULL;
	return (args);
}

int	ft_strptr(char **ptr)
{
	int i;

	i = 0;
	while (ptr[i])
		i++;
	return (i);
}

void	ft_add_back_cmd(t_cmds **cmds, t_cmds *new)
{
	t_cmds *ptr;

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

char *get_cmd_path(t_cmds *cmds)
{
	char *path;
	char *cmd_path;
	char *tmp;
	int i;

	i = 0;
	path = getenv("PATH");
	if (!path)
		return (NULL);
	while (path[i])
	{
		if (path[i] == ':')
		{
			tmp = ft_substr(path, 0, i);
			cmd_path = ft_strjoin(tmp, "/");
			free(tmp);
			tmp = ft_strjoin(cmd_path, cmds->args[0]);
			free(cmd_path);
			if (access(tmp, X_OK) == 0)
				return (tmp);
			free(tmp);
			path += i + 1;
			i = 0;
		}
		i++;
	}
	//printf("minishell: %s: command not found\n", cmds->args[0]);
	return (NULL);
}

t_cmds	*ft_fillup_struct(t_data *data)
{
	int i;
	int	last_io[2]; // last_io[0] -> in; last_io[1] -> out
	int	is_exec;
	int	sync_lines;
    t_cmds *new_cmd;
    t_cmds *head_cmd;

	i = 0;
	sync_lines = 0;
	is_exec = 0;
    head_cmd = 0;
	while (data->splitted_tokens[i])
	{
		new_cmd = (t_cmds*)malloc(sizeof(t_cmds));
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
	data.here_fds = (int **)malloc(sizeof(int*) * (ft_strptr(data.splitted_tokens)));
	i = -1;
	sync_lines = 0;
	while (data.splitted_tokens[++i])
	{
		data.here_fds[i] = ft_open_hdocs(data.lines, data.splitted_tokens[i], &sync_lines);
		sync_lines++;
	}
	/* open infiles */
	data.infiles = (int **)malloc(sizeof(int*) * (ft_strptr(data.splitted_tokens)));
	i = -1;
	sync_lines = 0;
	while (data.splitted_tokens[++i])
	{
		data.infiles[i] = ft_open_infiles(data.lines, data.splitted_tokens[i], &sync_lines);
		sync_lines++;	
	}
	/* open outfiles */
	data.outfiles = (int **)malloc(sizeof(int*) * (ft_strptr(data.splitted_tokens)));
	i = 0;
	sync_lines = 0;
	while (data.splitted_tokens[i])
	{
		data.outfiles[i] = ft_open_outfiles(data.lines, data.splitted_tokens[i], &sync_lines);
		sync_lines++;
		i++;
	}
    /* fillup the linked list struct */
	cmds = ft_fillup_struct(&data);
	i = 0;
	while (cmds)
	{
		i = 0;
		while(cmds->args[i])
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

int	count_dup(char *str_trim, char o)
{
	int i;

	i = 0;
    while (str_trim[i] == o)
        i++;
    return (i);
}

char	check_pipe(char	*arg)
{
	int count;
	int	i;

	i = 0;
	count = count_dup(arg, '|');
	if (count > 1)
		return ('E');
	else
		return ('|');
}

char	check_in(char *arg)
{
	int i;
	int count;

	i = 0;
	count = count_dup(arg, '<');
	if (count == 1)
		return('<');
	else if (count == 2)
		return('H');
	else
		return('E');
}

char	check_out(char	*arg)
{
	int	i;
	int	count;

	i = 0;
	count = count_dup(arg, '>');
	if (count == 1)
		return ('>');
	else if (count == 2)
		return ('A');
	else
		return ('E');
}

char    *ft_tokenize(char **lines)
{
    int		i;
	int		k;
	int		len;
    char	*tokenized_arr;

	i = 0;
	len = 0;
    k = 0;
	while (lines[len])
		len++;
	tokenized_arr = ft_calloc(len + 1, sizeof(char *));
    while(lines[i] != '\0')
    {
		if (*lines[i] == '|')
			tokenized_arr[k] = check_pipe(lines[i]);
		else if (*lines[i] == '<')
			tokenized_arr[k] = check_in(lines[i]);
		else if (*lines[i] == '>')
			tokenized_arr[k] = check_out(lines[i]);
		else
			tokenized_arr[k] = 'S';
		k++;
		i++;
	}
	tokenized_arr[k] = '\0';
	//i = 0;
	// while(tokenized_arr[i])
	// {
	// 	printf("%c", tokenized_arr[i]);
	// 	i++;
	// }
	// printf("\n");
    return (tokenized_arr);
}
