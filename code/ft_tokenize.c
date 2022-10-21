/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:16:45 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/19 23:18:32 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	count_dup(char *str_trim, char o)
{
	int	i;

	i = 0;
	while (str_trim[i] == o)
		i++;
	return (i);
}

char	check_pipe(char	*arg)
{
	int	count;

	count = count_dup(arg, '|');
	if (count > 1)
		return ('E');
	else
		return ('|');
}

char	check_in(char *arg)
{
	int	count;

	count = count_dup(arg, '<');
	if (count == 1)
		return ('<');
	else if (count == 2)
		return ('H');
	else
		return ('E');
}

char	check_out(char	*arg)
{
	int	count;

	count = count_dup(arg, '>');
	if (count == 1)
		return ('>');
	else if (count == 2)
		return ('A');
	else
		return ('E');
}

char	*ft_tokenize(char **lines)
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
	while (lines[i])
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
	while (tokenized_arr[i])
	{
		printf("%c", tokenized_arr[i]);
		i++;
	}
	printf("\n");
	return (tokenized_arr);
}
