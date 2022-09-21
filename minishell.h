/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:18:26 by abouhaga          #+#    #+#             */
/*   Updated: 2022/09/21 19:56:01 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_envp
{
    char            *key;
    char            *value;
    struct s_envp   *next;
} t_envp;


typedef struct s_gdata
{
    int     exit_status;
    t_envp  env;
} t_gdata;

typedef struct s_cmds
{
    char    *path;
    char    **args;
    int     in;
    int     out;
} t_cmds;

void    ft_parser(char *line);
char	*ft_strtrim(char *s, char *set);
char    *ft_tokenize(char **lines);
#endif
