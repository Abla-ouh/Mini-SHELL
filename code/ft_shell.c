/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:54:04 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/23 22:18:22 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

unsigned short	g_exit_code = EXIT_SUCCESS;

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_cmds	*cmds;

	(void)av;
	if (ac != 1 || !*env)
		return (1);
	glob.envx = env_list(env);
	while (1)
	{
		line = readline("\e[1;95mminishell$  \e[0m");
		if (!line)
		{
			free(line);
			exit(0);
		}
		if (!(*line))
		{
			free(line);
			continue ;
		}
		add_history(line);
		cmds = ft_parser(line);
		free(line);
	}
	return (0);
}
