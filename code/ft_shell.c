/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:54:04 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/25 06:10:27 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

unsigned short	g_exit_code = EXIT_SUCCESS;

int	main(int ac, char **av, char **env)
{
	(void)av;
	char	*line;
	t_cmds	*shel_l;

	if (ac != 1 || !(*env))
		return (1);
	glob_init(env);
	while(1)
	{
		signal_stream();
	    line = readline("\e[1;95mminishell$>  \e[0m");
	    if (!line)
	    {
	        free(line);
	        exit(0);
	    }
		if (ft_strlen(line) > 0)
		{
			add_history(line);
			shel_l = ft_parser(line);
			ft_run_cmds(shel_l);
		}
	}
	//ft_reset_glob();
	return (0);
}
