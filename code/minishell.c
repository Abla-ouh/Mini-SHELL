/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:54:04 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/10 16:04:51 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int main(int ac, char **av, char **env)
{
	(void)av;
	char	*line;
	t_cmds	*shel_l;
	line = NULL;

	glob_init(env);
	//ft_env(glob.envx);
	if (ac != 1 || !*env)
		return (1);
	while(1)
	{
	    line = readline("minishell$ ");
	    if (!line)
	    {
	        free(line);
	        exit(0);
	    }
		if (ft_strlen(line) > 0)
			add_history(line);
	    shel_l = ft_parser(line);
		ft_exec(shel_l);
	}
	return (0);
}