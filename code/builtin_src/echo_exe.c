/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:57:32 by midfath           #+#    #+#             */
/*   Updated: 2022/10/05 16:38:39 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exe.h>

void	ft_echo(char **ar)
{
	int	i;
	int	j;

	i = 1;
	while (ar[i])
	{
		if (ar[i][0] != '-')
			break ;
		j = 1;
		while (ar[i][j] && ar[i][j] == 'n')
			j++;
		if (!ar[i][j] && j > 1)
			i++;
		else
			break ;
	}
	j = (i == 1);
	while (ar[i])
	{
		ft_putstr(ar[i]);
		if (ar[(i++) + 1])
			write(1, " ", 1);
	}
	if (j)
		write(1, "\n", 1);
}
