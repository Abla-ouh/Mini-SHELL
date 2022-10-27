/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:54:04 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/27 20:21:18 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_cmds	*shel_l;
	t_cmds	*tmp;

	(void) av;
	if (ac != 1 || !(*env))
		return (1);
	g_glob_init(env);
	while (1)
	{
		signal_stream();
		line = readline("\e[1;95mminishell$> \e[0m");
		if (!line)
			exit(g_glob.exit_status);
		if (ft_strlen(line) > 0)
		{
			add_history(line);
			shel_l = ft_parser(line);
			tmp = shel_l;
			ft_run_cmds(shel_l);
		}
		free(line);
	}
	ft_reset_g_glob();
	return (0);
}
