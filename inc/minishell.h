/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:18:26 by abouhaga          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/24 22:16:20 by midfath          ###   ########.fr       */
=======
/*   Updated: 2022/09/24 17:58:36 by abouhaga         ###   ########.fr       */
>>>>>>> origin/master
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "exe.h"

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
    int     is_exec;
} t_cmds;

t_cmds  *ft_parser(char *line);
int     count_dup(char *str_trim, char o);
char	*ft_str_trim(char *s, char *set);
char    *ft_tokenize(char **lines);
#endif
