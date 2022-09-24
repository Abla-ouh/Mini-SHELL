/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lunch_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:21:05 by abouhaga          #+#    #+#             */
/*   Updated: 2022/09/24 16:04:51 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

void	ft_read_stdin(int *here_fds, char **lines, int del_idx)
{
	char *temp;
	
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
}

int find_here_docs(char *tokens)
{
	int i;
	int her;

	i = 0;
	her = 0;
	while (tokens[i])
	{
		if (tokens[i] == 'H')
			her++;
		i++;
	}
	return (her);
}

int	**ft_open_hdocs(char **lines, char *tokens)
{
	int	**here_fds;
	int	here_num;
	int	i;
	int j;

	here_num = find_here_docs(tokens);
	if (!here_num)
		return (NULL);
	here_fds = malloc(sizeof(int *) * (here_num + 1));
	i = 0;
	j = 0;
	printf("count = %d\n", here_num);
	while (i < here_num)
	{
		here_fds[i] = malloc(sizeof(int) * 2);
		while(tokens[j] && tokens[j] != 'H')
			j++;
		ft_read_stdin(here_fds[i], lines , ++j);
		i++;
	}
	return (here_fds);
}

t_cmds	*ft_parser(char *line)
{
	char	**lines;
    char    *tokens;
	int		**here_fds;
	//int		*infiles;
	//int		*outfiles;
	t_cmds	*cmds;

    lines = ft_lexer(line, " \t\r\v\f\n");
	tokens = ft_tokenize(lines);
    if (ft_syntax_error(lines, tokens))
		return (NULL);
    if (ft_check_redir_filename(lines, tokens))
		return (NULL);
	here_fds = ft_open_hdocs(lines, tokens);
	
	/* open infiles */
	/* open outfiles */
    /* fillup the linked list struct */
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
	i = 0;
	while(tokenized_arr[i])
	{
		printf("%c", tokenized_arr[i]);
		i++;
	}
	printf("\n");
    return (tokenized_arr);
}
