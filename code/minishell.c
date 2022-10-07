/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:54:04 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/07 08:08:27 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <exe.h>

int main(int ac, char **av, char **env)
{
    (void)av;
    char	*line;
    //char    *arr;
    t_cmds  *cmds;
    line = NULL;

    if (ac != 1 || !*env)
        return (1);
    ft_parser("< token cat \"$m'eee$'ee\" | ls hello | > nors ww w");
    // while(1)
    // {
    //     line = readline("minishell$ ");
    //     if (!line)
    //     {
    //         free(line);
    //         exit(0);
    //     }
        // if (ft_strlen(line) > 0)
		// 	add_history(line);
    //     ft_parser(line);
    // }
    return (0);
}