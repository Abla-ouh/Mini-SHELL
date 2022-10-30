/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:46:46 by midfath           #+#    #+#             */
/*   Updated: 2022/10/29 22:02:15 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exe.h>

int	ft_check_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != '+')
			return (1);
		i++;
	}
	return (0);
}

int	ft_exit(char **ar)
{
	long int	sig;

	sig = 0;
	if (!ar[1])
	{
		ft_reset_g_glob();
		exit (g_glob.exit_status);
	}
	if (ft_check_digits(ar[1]))
	{
		ft_perror("exit", ar[1], "numeric arguement required");
		exit(255);
	}
	sig = ft_atoi(ar[1]);
	if (sig && !ar[2])
		exit(sig % 256);
	else
	{
		ft_perror("exit", "NULL", "too many arguments");
		return (1);
	}
}
