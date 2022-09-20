/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:54:04 by abouhaga          #+#    #+#             */
/*   Updated: 2022/09/20 00:44:41 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
    (void)av;
    char	*line;
    line = NULL;
    if (ac != 1 || !*env)
        return (1);
    ft_parser("e<cho<  ||| klas<<<<<<djflk\" allaskdj<<<fl llaksdjf laskdfj lkasjdf \"lasdjfkasdjf \'asdjfl\' ks\t");
    // while(1)
    // {
    //     line = readline("minishell$ ");
    //     if (!line)
    //     {
    //         free(line);
    //         exit(0);
    //     }
    //     if (ft_strlen(line) > 0)
	// 		add_history(line);
    //     ft_parser(line);
    // }
    return (0);
}