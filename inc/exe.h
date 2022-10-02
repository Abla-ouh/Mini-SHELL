/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 21:39:49 by midfath           #+#    #+#             */
/*   Updated: 2022/10/01 18:11:31 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXE_H
# define EXE_H
# include "../libft/libft.h"
# include "minishell.h"

typedef struct s_env
{
	char	*title;
	char	*value;
}t_env;


typedef struct s_gexe
{
    int     exit_status;
    t_list  *env;
	char	*p_cwd;
} t_gexe;

/*the builtin cd*/
int	ft_cd(t_list env ,char **av, t_gexe *gdexe);

/*the chdir func but change the oldpwd and update the pwd */
int	chdir_update(char *dir, t_list *env, t_gexe *gdexe);

/*find title and return the value addres */
char **find_title(t_list *env, char *title);

 /*ft_getp_cwd the getcwd  func but never fail because of buff size*/
int	ft_getp_cwd(char **p_cwd);

#endif 