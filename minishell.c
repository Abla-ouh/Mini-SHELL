/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:54:04 by abouhaga          #+#    #+#             */
/*   Updated: 2022/09/17 23:00:17 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
    char *line;
    line = NULL;

    if (ac != 1 || !*env)
        return (1);
    ft_lexer("echo lkasdjflk\" allaskdjfl llaksdjf laskdfj lkasjdf \"lasdjfkasdjf\'asdjflks");
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
    //      // line = ft_lexer(line);
    //     ft_lexer(line);
    // }
    return (0);
}