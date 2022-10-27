/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:35:25 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/26 11:02:30 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	find_string(char *str_trim, int *i)
{
	while (is_seperator_char(str_trim[*i]))
	{
		if (str_trim[*i] == '\"' || str_trim[*i] == '\'')
			skip_quote(str_trim, i, str_trim[*i]);
		else
			(*i)++;
	}
}

void	skip_quote(char *str_trim, int *i, char q)
{
	(*i)++;
	while (str_trim[*i] && str_trim[*i] != q)
		(*i)++;
	if (str_trim[*i] == q)
		(*i)++;
}

int	find_until_not(char *str_trim, int *i, char o)
{
	while (str_trim[*i] == o)
		(*i)++;
	return (1);
}

void	count_until_not(char *trim_line, int i, int *len, char o)
{
	while (trim_line[i + (*len)] == o)
		(*len)++;
}

void	count_string(char *trim_line, int i, int *len)
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
