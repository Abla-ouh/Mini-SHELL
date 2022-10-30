/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:54:04 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/30 14:11:57 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static	void	init_mini(void)
{
	g_glob.sig_c = 0;
	signal_stream();
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_cmds	*shel_l;

	g_glob_init(env);
	while (ac || av)
	{
		init_mini();
		line = readline("\e[1;95mminishell$> \e[0m");
		if (!line)
			exit (g_glob.exit_status);
		if (ft_strlen(line) > 0)
		{
			add_history(line);
			shel_l = ft_parser(line);
			if (!shel_l)
				g_glob.exit_status = 258;
			else if (g_glob.sig_c != 1)
				ft_run_cmds(shel_l);
			ft_free_all(shel_l);
		}
		free(line);
	}
	ft_reset_g_glob();
	return (0);
}
