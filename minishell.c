/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:54:04 by abouhaga          #+#    #+#             */
/*   Updated: 2022/09/21 23:42:16 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* "<< infile cat /etc/passwd  '|' awk '{printf' | echo  lkasdjflk\" allaskdjfl llaksdjf laskdfj lkasjdf \"lasdjfkasdjf'asdjflksajdflkasjdf asdfkasldj flkasjdf lkasdjf ' | pwd" */

int main(int ac, char **av, char **env)
{
    (void)av;
    char	*line;
    char    *arr;
    line = NULL;

    if (ac != 1 || !*env)
        return (1);
    ft_parser("<< stop1 cat << stop2");
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