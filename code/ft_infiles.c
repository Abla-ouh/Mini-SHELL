/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_infiles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:24:26 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/23 21:47:28 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	*ft_open_infiles(char **lines, char *tokens, int *sync_lines)
{
	int	i;
	int	j;
	int	in;
	int	*infiles;

	in = find_op(tokens, '<');
	if (!in)
	{
		*sync_lines += ft_strlen(tokens);
		return (NULL);
	}
	infiles = malloc(sizeof(int) * (in));
	i = 0;
	j = 0;
	while (i < in)
	{
		while (tokens[j] && tokens[j] != '<')
		{
			j++;
			(*sync_lines)++;
		}
		if (!tokens[j])
			break ;
		if (tokens[j] == '<' && access(lines[*sync_lines + 1], F_OK) == -1)
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
	while (tokens[j++])
		(*sync_lines)++;
	return (infiles);
}