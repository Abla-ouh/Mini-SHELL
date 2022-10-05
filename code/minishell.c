/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:54:04 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/05 08:39:29 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../inc/minishell.h>

int main(int ac, char **av, char **env)
{
    (void)av;
    char	*line;
    //char    *arr;
    t_cmds  *cmds;
    line = NULL;

    if (ac != 1 || !*env)
        return (1);
    // ft_parser("< token cat meeeee | hh jdjd fewefwewer owefjwejfiojijoijwfj | > nors ww w");
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
        cmds = ft_parser(line);
        ft_exec(cmds);
    }
    return (0);
}