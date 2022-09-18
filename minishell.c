/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:54:04 by abouhaga          #+#    #+#             */
/*   Updated: 2022/09/18 18:22:31 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	get_len(char *line, char *set);
int main(int ac, char **av, char **env)
{
    char *line;
    line = NULL;
    if (ac != 1 || !*env)
        return (1);
    // printf("%d\n", get_len("  <<a>>b echo lkasdjflk\" allaskdjfl llaksdjf laskdfj lkasjdf \"lasdjfkasdjf\'asdjfl\' ks\t", " \t\r\v\f\n"));
    ft_lexer("   echo klas<<<<<<djflk\" allaskdj<<<fl llaksdjf laskdfj lkasjdf \"lasdjfkasdjf \'asdjfl\' ks\t");
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
         // line = ft_lexer(line);
        ft_lexer(line);
    }
    return (0);
}