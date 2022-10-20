/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:46:46 by midfath           #+#    #+#             */
/*   Updated: 2022/10/20 21:35:32 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exe.h>

int	ft_check_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i])  && str[i] != '-' && str[i] != '+')
			return (1);
		i++;
	}
		return (0);
}

int	ft_exit(char **ar)
{
	long int	sig;

	sig = 0;
	// if ()
	// {
		if (!ar[1])
			exit(glob.exit_status);	
		if (ft_check_digits(ar[1]))
		{
			ft_perror("exit", ar[1], "numeric arguement required");
			exit(255);
		}
		sig = ft_atoi(ar[1]);
		//printf("%lu\n", sig);
		if (sig && !ar[2])
			exit(sig % 256);
	// }
	else
	{
		ft_perror("exit",  NULL, "too many arguments");
		exit(255);
	}
	return(0);
}