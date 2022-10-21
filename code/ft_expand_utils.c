/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:37:39 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/19 23:38:17 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_single_quoted(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'')
		{
			skip_quote(arg, &i, '\'');
			if (arg[i - 1] != '\'')
				return (0);
		}
		else
			i++;
	}
	return (1);
}
