/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_outfiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:25:13 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/27 21:53:23 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	outfiles_fail(char **lines, char *tokens, t_cord *cords, int *outfiles)
{
	if ((tokens[cords->j] == '>' || tokens[cords->j] == 'A')
		&& access(lines[(*cords->sync) + 1], F_OK) == -1)
	{
		outfiles[cords->i] = open(lines[(*cords->sync) + 1],
				O_CREAT | O_WRONLY, 0644);
		cords->i++;
		cords->j++;
		(*cords->sync)++;
		return (1);
	}
	else if (access(lines[(*cords->sync) + 1], W_OK) == -1)
	{
		outfiles[cords->i] = F_PERMISSION_DENIED;
		printf("minishell: %s: Permission denied\n", lines[cords->j + 1]);
		cords->i++;
		cords->j++;
		(*cords->sync)++;
		return (1);
	}
	return (0);
}

void	to_open(t_cord *cords, char *tokens, char **lines, int *outfiles)
{
	if (tokens[cords->j] == '>')
		outfiles[cords->i] = open(lines[(*cords->sync) + 1],
				O_TRUNC | O_WRONLY, 0644);
	else
		outfiles[cords->i] = open(lines[(*cords->sync) + 1],
				O_CREAT | O_APPEND | O_WRONLY, 0644);
}

void	init_cords(int *sync, t_cord *cords)
{
	cords->i = -1;
	cords->j = -1;
	cords->sync = sync;
}

int	count_check_out(int out, char *tokens, t_cord *cords)
{
	out = find_op(tokens, '>');
	out += find_op(tokens, 'A');
	if (!out)
	{
		cords->sync += ft_strlen(tokens);
		return (-1);
	}
	return (out);
}

int	*ft_open_outfiles(char **lines, char *tokens, int *sync)
{
	t_cord	cords;
	int		*outfiles;
	int		out;

	out = 0;
	init_cords(sync, &cords);
	out = count_check_out(out, tokens, &cords);
	if (out == -1)
		return (NULL);
	outfiles = malloc(sizeof(int) * (out));
	while (++cords.i < out)
	{
		while (tokens[++cords.j] && (tokens[cords.j] != '>'
				&& tokens[cords.j] != 'A'))
			(*sync)++;
		if (!tokens[cords.j])
			break ;
		if (outfiles_fail(lines, tokens, &cords, outfiles) == 1)
			continue ;
		to_open(&cords, tokens, lines, outfiles);
		cords.j++;
		*sync += 1;
	}
	*sync += ft_strlen(&tokens[cords.j]);
	return (outfiles);
}
