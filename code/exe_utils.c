/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:29:26 by midfath           #+#    #+#             */
/*   Updated: 2022/10/30 03:22:25 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exe.h>

void	ft_wait_cmd(pid_t pid)
{
	waitpid(pid, &g_glob.exit_status, 0);
	if (WIFSIGNALED(g_glob.exit_status))
	{
		g_glob.exit_status = WIFSIGNALED(g_glob.exit_status) + 129;
		return ;
	}
	else
		g_glob.exit_status = WEXITSTATUS(g_glob.exit_status);
	while (wait(&g_glob.exit_status) != -1)
		;
}

char	**env_lst_to_matrix(t_list *lst)
{
	int		size;
	char	**env;
	char	*tmp;
	t_list	*env_list;

	tmp = NULL;
	env_list = lst;
	size = ft_lstsize(env_list);
	env = malloc((sizeof(char *) * (size + 1)));
	size = 0;
	while (env_list)
	{
		tmp = ft_strjoin("=", ((t_env *)env_list->content)->value);
		env[size] = ft_strjoin(((t_env *)env_list->content)->title, tmp);
		free(tmp);
		if (!(env[size]))
			ft_arrfreey();
		size++;
		env_list = env_list->next;
	}
	env[size] = NULL;
	return (env);
}

void	ft_reset_g_glob(void)
{
	ft_lstclear(&g_glob.envx, free);
	g_glob.envx = NULL;
	ft_arrfreey();
	g_glob.env = NULL;
	exit (g_glob.exit_status);
}

int	check_exe(t_cmds *shel_l)
{
	if (!shel_l || !shel_l->is_exec)
		return (0);
	return (1);
}

void	ft_closethemall(t_cmds *node_cmd, int *p_fd)
{
	close(p_fd[WR_END]);
	if (g_glob.perv_fd)
		close(g_glob.perv_fd);
	if (!ft_isbuiltin(node_cmd))
	{
		if (node_cmd->in > 0)
			close(node_cmd->in);
		if (node_cmd->out > 1)
			close(node_cmd->out);
		g_glob.perv_fd = p_fd[RD_END];
		close(p_fd[RD_END]);
	}
}
