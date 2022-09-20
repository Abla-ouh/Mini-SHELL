/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lunch_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:21:05 by abouhaga          #+#    #+#             */
/*   Updated: 2022/09/20 00:46:05 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	str_trim = ft_strtrim(line, set);
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
    while (trim_line[i + (*len)] && trim_line[i + (*len)] != q)//keep iterating until next quote 
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

void	ft_parser(char *line)
{
	char	**lines;
	int	i;

	i = 0;
    lines = ft_lexer(line, " \t\r\v\f\n");
	while(lines[i])
	{
		printf("%s\n", lines[i]);
		i++;
	}
	exit(1);
	//ft_tokenize(lines);
}

char	scan_str(char *line)
{
	//char	type;
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '|')
			return('P');
		else if (line[i] == '<' && line[i + 1] == '<')
			return('H');
		else if (line[i] == '<' && line[i + 1] == '<')
			return('A');
		else if (line[i] == '<')
			return('<');
		else if(line[i] = '>')
			return('>');
		else
			return('E');
		i++;
	}
}

char    *ft_tokenize(char **lines)
{
    int		i;
	int		j;
    int     k;
	int		len;
    char	*tokenized_arr;

	i = 0;
	len = 0;
	while (lines[len])
		len++;
	tokenized_arr = ft_calloc(len + 1, sizeof(char *));
    while(lines)
    {
        if (scan_arg(lines[i]) == 'P')
            tokenized_arr[k] = 'P';
        else if (scan_arg(lines[i]) == 'H')
            tokenized_arr[k] = 'H';
		else if (scan_arg(lines[i]) == 'S')
            tokenized_arr[k] = 'S';
		else if (scan_arg(lines[i]) == 'A')
			tokenized_arr[k] = 'A';
		else if (scan_arg(lines[i]) == '>')
			tokenized_arr[k] = '>';
		else if (scan_arg(lines[i]) == '<')
			tokenized_arr[k] = '<';
		else
			tokenized_arr[k] = /* smtg else*/
		k++;
		i++;
    }
}
