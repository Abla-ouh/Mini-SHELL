/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 21:39:49 by midfath           #+#    #+#             */
/*   Updated: 2022/10/30 09:20:20 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXE_H
# define EXE_H
# include "../libft/libft.h"
# include <errno.h>
# include <unistd.h>
# include <minishell.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <readline/readline.h>
# include <sys/ioctl.h>

# define RD_END 0
# define WR_END 1

typedef struct s_env
{
	char	*title;
	char	*value;
}	t_env;

typedef struct s_cmds	t_cmds;
typedef struct s_gexe
{
	char	**env;
	int		exit_status;
	t_list	*envx;
	int		infd;
	int		outfd;
	int		sig_c;
	int		flag;
	int		perv_fd;
	pid_t	last_pid;
}	t_gexe;

t_gexe					g_glob;

void	ft_run_cmds(t_cmds *cmds);
void	ft_wait_cmd(void);
int		ft_isbuiltin(t_cmds *shel_l);
int		run_builtin(t_cmds *shel_l, int flag);
int		ft_perror(char *cmd, char *flag, char *msg);
int		ft_cmd_exe(t_cmds *shel_l, t_cmds *node_cmd);
int		sub_process(t_cmds *shel_l, t_cmds *node_cmd, int *p_fd);
void	redi_sub(t_cmds *node_cmd, int p_fd[2]);
void	builtin_sub(t_cmds *node_cmd);
char	**env_lst_to_matrix(t_list *env_list);
void	ft_reset_g_glob(void);
int		check_exe(t_cmds *shel_l);
void	exe_file(t_cmds *node_cmd);
int		exe_cmd(t_cmds *node_cmd);
void	exe_builtin(t_cmds *node_cmd);
void	signal_stream(void);
void	handler(int sig);
void	sig_handler_heredoc(int sig);

/*init the gdexe struct*/
void	g_glob_init(char **env);

/*********************** the builtin env ************************/
int		ft_env(char **av, t_list *env);

/*convert the char **env to lst*/
char	**ft_empty_env(char **env);
t_env	*init_lst_env(void);
t_env	*env_str(char *str);
t_list	*env_list(char **env);
void	var_export(char **var, t_list *new);

/*find title in env lst and return the value addres */
char	**find_title(char *title);

/*ft_getp_cwd the getcwd  func but never fail because of buff size*/
int		ft_getp_cwd(char **p_cwd);

/*********************** the builtin cd **************************/
int		ft_cd(char **av);
int		cd_option(char *dir);

/*the chdir func but change the oldpwd and update the pwd */
int		chdir_update(char *dir);
void	pwd_update(void);
/*********************** the builtin exit **************************/
int		ft_exit(char **ar);

// /*atoi but convert to unsigned int */
// unsigned int	ft_atoui(char *nb, unsigned int *ptr);

/*********************** the builtin echo **************************/
int		ft_echo(char **ar);

/*********************** the builtin unset **************************/
int		ft_unset(char **ar);

/*********************** the builtin pwd **************************/
int		ft_pwd(char **ar);

/*********************** the builtin export **************************/
void	put_export(void);
int		var_cat(char **var);
char	**get_var(char *str);
int		ft_export(char **var);
int		vars_check(char *var);
int		var_update(char **var);
void	export_var(char *input);

/********************************************************************/

void	ft_arrfreey(void);
char	*return_value(char *title);
int		path_changer(char **o_pwd, char *cwd);
void	ft_closethemall(t_cmds *node_cmd, int *p_fd);

#endif