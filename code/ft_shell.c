/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:54:04 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/21 12:37:01 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

unsigned short	g_exit_code = EXIT_SUCCESS;

int	main(int ac, char **av, char **env)
{
	char	*line;

	(void)av;
	line = NULL;
	if (ac != 1 || !*env)
		return (1);
	glob.envx = env_list(env);
	while (1)
	{
		line = readline("minishell$ ");
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
		if (ft_strlen(line) > 0)
			add_history(line);
		ft_parser(line);
		free(line);
	}
	return (0);
}
