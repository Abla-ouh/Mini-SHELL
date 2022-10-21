/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_outfiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:25:13 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/19 23:26:02 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	*ft_open_outfiles(char **lines, char *tokens, int *sync_lines)
{
	int	i;
	int	j;
	int	out;
	int	*outfiles;

	out = find_op(tokens, '>');
	out += find_op(tokens, 'A');
	i = 0;
	if (!out)
	{
		while (tokens[i++])
			(*sync_lines)++;
		return (NULL);
	}
	j = 0;
	outfiles = malloc(sizeof(int) * (out));
	while (i < out)
	{
		while (tokens[j] && (tokens[j] != '>' && tokens[j] != 'A'))
		{
			j++;
			(*sync_lines)++;
		}
		if (!tokens[j])
			break ;
		if ((tokens[j] == '>' || tokens[j] == 'A')
			&& access(lines[*sync_lines + 1], F_OK) == -1)
		{
			outfiles[i] = open(lines[*sync_lines + 1],
					O_CREAT | O_WRONLY, 0644);
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
			outfiles[i] = open(lines[*sync_lines + 1],
					O_TRUNC | O_WRONLY, 0644);
		else
			outfiles[i] = open(lines[*sync_lines + 1], O_APPEND, 0644);
		i++;
	}
	while (tokens[j++])
		(*sync_lines)++;
	return (outfiles);
}