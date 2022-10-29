/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_infiles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:24:26 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/29 18:46:33 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	infiles_fail(char **lines, char *tokens, t_cord	*cords, int *infiles)
{
	if (tokens[cords->j] == '<'
		&& access(lines[(*cords->sync) + 1], F_OK) == -1)
	{
		infiles[cords->i] = F_NO_SUCH_FILE;
		g_glob.flag = -1;
		ft_fprintf(2, "minishell: %s: No such file or directory\n", \
			lines[cords->j + 1]);
		cords->i++;
		cords->j++;
		(*cords->sync)++;
		return (F_NO_SUCH_FILE);
	}
	else if (tokens[cords->j] == '<'
		&& access(lines[(*cords->sync) + 1], R_OK) == -1)
	{
		infiles[cords->i] = F_PERMISSION_DENIED;
		g_glob.flag = -1;
		ft_fprintf(2, "minishell: %s: Permission denied\n", \
			lines[cords->j + 1]);
		cords->i++;
		cords->j++;
		(*cords->sync)++;
		return (F_PERMISSION_DENIED);
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
		if (!tokens[cords.j]
			|| infiles_fail(lines, tokens, &cords, infiles) < 0)
			break ;
		infiles[cords.i] = open(lines[*sync + 1], O_RDONLY);
		cords.i++;
	}
	*sync += ft_strlen(&tokens[cords.j]);
	return (infiles);
}
