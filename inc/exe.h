/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 21:39:49 by midfath           #+#    #+#             */
/*   Updated: 2022/10/06 11:25:29 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXE_H
# define EXE_H
# include "../libft/libft.h"
# include <errno.h>
# include <unistd.h>
# include <minishell.h>

typedef struct s_env
{
	char	*title;
	char	*value;
}t_env;

typedef struct s_cmds t_cmds;

typedef struct s_gexe
{
	char	**env;
	int     exit_status;
	t_list  *envx;
} t_gexe;

t_gexe glob;

int	ft_exec(t_cmds *cmds);

/*init the gdexe struct*/
int	gdexe_init(t_gexe *exe, char **env);

/*********************** the builtin env ************************/
int	ft_env(t_list *env, t_gexe *flag);

/*convert the char **env to lst*/
t_env	*init_lst_env(void);
t_env	*env_str(char *str);
t_list	*env_list(char **env);

/*find title in env lst and return the value addres */
char **find_title(t_list *env, char *title);

 /*ft_getp_cwd the getcwd  func but never fail because of buff size*/
int	ft_getp_cwd(char **p_cwd);

/*********************** the builtin cd **************************/
int	ft_cd(t_list *env ,char **av, t_gexe *gdexe);
int	cd_option(char *dir, t_list *env, t_gexe *gdexe);

/*the chdir func but change the oldpwd and update the pwd */
int	chdir_update(char *dir, t_list *env, t_gexe *gdexe);

/*********************** the builtin exit **************************/
int	ft_exit(char **ar);

/*********************** the builtin echo **************************/
int	ft_echo(char **ar);

#endif 