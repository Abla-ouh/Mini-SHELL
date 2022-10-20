/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 10:44:30 by midfath           #+#    #+#             */
/*   Updated: 2022/10/15 10:56:02 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exe.h>

int	ft_perror(char *cmd, char *flag, char *msg)
{
	ft_putstr_fd("\033[1;31mminishell:\033[0m ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (flag)
	{
		ft_putstr_fd("`", 2);
		ft_putstr_fd(flag, 2);
		ft_putstr_fd("': ", 2);
	}
	if (errno && !msg)
		msg = strerror(errno);
	if (msg)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putendl_fd(msg, 2);
	}
	return (1);
}