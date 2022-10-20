/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:54:04 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/20 18:24:42 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int main(int ac, char **av, char **env)
{
	(void)av;
	char	*line;
	t_cmds	*shel_l;
	line = NULL;

	if (ac != 1 || !*env)
		return (1);
	glob_init(env);
	while(1)
	{
	    line = readline("minishell$> ");
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
	ft_reset_glob();
	return (0);
}