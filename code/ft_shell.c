/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:54:04 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/26 10:46:46 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

unsigned short	g_exit_code = EXIT_SUCCESS;

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_cmds	*shel_l;

	(void)av;
	if (ac != 1 || !(*env))
		return (1);
	glob_init(env);
	glob.infd = dup(0);
	glob.outfd = dup(1);
	while (1)
	{
		signal_stream();
		line = readline("\e[1;95mminishell$>  \e[0m");
		if (ft_strlen(line) > 0)
		{
			add_history(line);
			shel_l = ft_parser(line);
			ft_run_cmds(shel_l);
		}
		else
		{
			free(line);
			exit(glob.exit_status);
		}
	}
	//ft_reset_glob();
	return (0);
}
