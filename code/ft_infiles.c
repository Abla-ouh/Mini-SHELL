/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_infiles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:24:26 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/27 00:43:38 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	infiles_fail(char **lines, char *tokens, t_cord	*cords, int *infiles)
{
	if (tokens[cords->j] == '<'
		&& access(lines[(*cords->sync) + 1], F_OK) == -1)
	{
		infiles[cords->i] = F_NO_SUCH_FILE;
		printf("minishell: %s: No such file or directory\n", lines[cords->j + 1]);
		cords->i++;
		cords->j++;
		(*cords->sync)++;
		return (1);
	}
	else if (tokens[cords->j] == '<'
		&& access(lines[(*cords->sync) + 1], R_OK) == -1)
	{
		infiles[cords->i] = F_PERMISSION_DENIED;
		printf("minishell: %s: Permission denied\n", lines[cords->j + 1]);
		cords->i++;
		cords->j++;
		(*cords->sync)++;
		return (1);
	}
	return (0);
}

int	*ft_open_infiles(char **lines, char *tokens, int *sync)
{
	t_cord	cords;
	int		*infiles;

	cords.i = 0;
	cords.j = 0;
	cords.sync = sync;
	if (!find_op(tokens, '<'))
	{
		*sync += ft_strlen(tokens);
		return (NULL);
	}
	infiles = malloc(sizeof(int) * (find_op(tokens, '<')));
	while (cords.i < find_op(tokens, '<'))
	{
		while (tokens[cords.j] && tokens[cords.j] != '<')
		{
			cords.j++;
			(*sync)++;
		}
		if (!tokens[cords.j])
			break ;
		if (infiles_fail(lines, tokens, &cords, infiles) == 1)
			continue ;
		infiles[cords.i] = open(lines[*sync + 1], O_RDONLY);
		cords.i++;
	}
	*sync += ft_strlen(&tokens[cords.j]);
	return (infiles);
}

// int	*ft_open_infiles(char **lines, char *tokens, int *sync_lines)
// {
// 	int	i;
// 	int	j;
// 	int	in;
// 	int	*infiles;

// 	in = find_op(tokens, '<');
// 	if (!in)
// 	{
// 		*sync_lines += ft_strlen(tokens);
// 		return (NULL);
// 	}
// 	infiles = malloc(sizeof(int) * (in));
// 	i = 0;
// 	j = 0;
// 	while (i < in)
// 	{
// 		while (tokens[j] && tokens[j] != '<')
// 		{
// 			j++;
// 			(*sync_lines)++;
// 		}
// 		if (!tokens[j])
// 			break ;
// 		if (tokens[j] == '<' && access(lines[*sync_lines + 1], F_OK) == -1)
// 		{
// 			infiles[i] = F_NO_SUCH_FILE;
// 			printf("minishell: %s: No such file or directory\n", lines[j + 1]);
// 			i++;
// 			j++;
// 			(*sync_lines)++;
// 			continue ;
// 		}
// 		else if (access(lines[*sync_lines + 1], R_OK) == -1)
// 		{
// 			infiles[i] = F_PERMISSION_DENIED;
// 			printf("minishell: %s: Permission denied\n", lines[j + 1]);
// 			i++;
// 			j++;
// 			(*sync_lines)++;
// 			continue ;
// 		}	
// 		infiles[i] = open(lines[*sync_lines + 1], O_RDONLY);
// 		i++;
// 	}
// 	while (tokens[j++])
// 		(*sync_lines)++;
// 	return (infiles);
// }