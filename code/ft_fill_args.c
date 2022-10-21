/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:29:36 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/21 12:05:41 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	args_to_alloc(char *tokens)
{
	int	i;
	int	s;

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

//modify echo
char	**ft_fill_args(char **lines, char *tokens, int *sync_lines)
{
	int		i;
	int		j;
	char	**args;

	i = -1;
	j = 0;
	args = (char **)malloc(sizeof(char **) * (args_to_alloc(tokens) + 1));
	if (!args)
		return (NULL);
	while (tokens[++i])
	{
		if (tokens[i] == 'S' && (i == 0 || tokens[i - 1] == 'S'))
		{
			args[j] = ft_strdup(lines[*sync_lines]);
			j++;
		}
		(*sync_lines)++;
	}
	args[j] = NULL;
	while (tokens[i++])
		(*sync_lines)++;
	return (args);
}
// char	**ft_fill_args(char **lines, char *tokens, int *sync_lines)
// {
// 	int		i;
// 	int		j;
// 	char	**args;

// 	i = 0;
// 	j = 0;
// 	args = (char **)malloc(sizeof(char **) * (args_to_alloc(tokens) + 1));
// 	if (!args)
// 		return (NULL);
// 	while (tokens[i])
// 	{
// 		if (tokens[i] == 'S' && (i == 0 || tokens[i - 1] == 'S'))
// 		{
// 			while (tokens[i] == 'S')
// 			{
// 				args[j] = ft_strdup(lines[*sync_lines]);
// 				j++;
// 				i++;
// 				(*sync_lines)++;
// 			}
// 			break ;
// 		}
// 		i++;
// 		(*sync_lines)++;
// 	}
// 	args[j] = NULL;
// 	while (tokens[i++])
// 		(*sync_lines)++;
// 	return (args);
// }
