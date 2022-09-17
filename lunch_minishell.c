/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lunch_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:21:05 by abouhaga          #+#    #+#             */
/*   Updated: 2022/09/17 23:15:05 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (ft_strchr(set, str_trim[i]) == NULL)
        len++;
    while(str_trim[i])
    {
        if(ft_strchr(set, str_trim[i]) != NULL)
            len++;
        i++;
    }
	free(str_trim);
    return (len);
}

int token_size(char *line, char *set)
{
    int i;
    int len;

    i = 0;
    len = 0;
    while(line[i])
    {
        if(ft_strchr(set, line[i]) != NULL)
            len++;
        i++;
    }
    return (len);
}

char **ft_split_blank(char *line, char *set)
{
	char **strs;
	int	arr_len;
	int i;
	int j;

    i = 0;
	if (line == NULL || set == NULL)
		return (NULL);
	arr_len = get_len(line, set);
    strs = ft_calloc(arr_len + 1, sizeof(*strs));
    if (strs == NULL)
        return (NULL);
    while (i < arr_len && line[i])
    {
        while(line[i] && ft_strchr(set, *line) != NULL)
            i++;
        strs[i] = ft_calloc(token_size(line, set) + 1, sizeof(*strs[i]));
        // if(strs[i] == NULL)
        //     return(ft_free(strs));
        j = 0;
        while(line[i])
        {
            if (line[i] == '<' || line[i] == '>' || line[i] == '|')
                strs[i][j] = line[i];
            else if (line[i] == '\"' || line[i] == '\'')
            {
                strs[i][j] = line[i];
                i++;
                while(line[i] != '\"' || line[i] != '\'')
                {
                    strs[i][j] = line[i];
                    i++;
                }
                strs[i][j] = line[i];
                if (ft_strchr(set, *line) == NULL)
                {
                    strs[i][j] = line[i];
                    j++;
                }
                else
                    break;
            }
            else
                strs[i][j] = line[i];
            j++;
        }
        i++;
    }
	return (strs);
}

char    **ft_lexer(char *line)
{
    int i;
    int j;
    i = 0;
    j = 0;
    char **lines;
    lines = ft_split_blank(line, " \t\r\v\f\n");
    // print lines here
    while(lines[i])
    {
        printf("%s\n", lines[i]);
        i++;
    }
    exit(1);
}
