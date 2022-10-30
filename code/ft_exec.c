/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:51:19 by midfath           #+#    #+#             */
/*   Updated: 2022/10/30 11:21:20 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exe.h>

void	signal_stream(void)
{
	signal(SIGINT, &handler);
	signal(SIGQUIT, SIG_IGN);
}

void	close_all_fds(t_cmds *shel_l)
{
	t_cmds	*nodes;

	nodes = shel_l;
	while (nodes)
	{
		if (nodes->in > 0)
			close(nodes->in);
		if (nodes->out > 1)
			close(nodes->out);
		nodes = nodes->next;
	}
}

int	sub_process(t_cmds *shel_l, t_cmds *node_cmd, int *p_fd)
{
	int	f;

	f = 0;
	redi_sub(node_cmd, p_fd);
	close(p_fd[RD_END]);
	close_all_fds(shel_l);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	f = ft_isbuiltin(node_cmd);
	if (f)
	{
		ft_arrfreey();
		exit(run_builtin(node_cmd, f));
	}
	if (!node_cmd->args[0])
	{
		ft_arrfreey();
		exit (127);
	}
	else if (ft_strchr(node_cmd->args[0], '/'))
		exe_file(node_cmd);
	else
		exe_cmd(node_cmd);
	exit (1);
}

int	ft_cmd_exe(t_cmds *shel_l, t_cmds *node_cmd)
{
	pid_t	pid;
	int		p_fd[2];

	if (pipe(p_fd) == -1)
		exit (1);
	g_glob.env = env_lst_to_matrix(g_glob.envx);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		ft_reset_g_glob();
	if (!pid)
		return (sub_process(shel_l, node_cmd, p_fd));
	close(p_fd[WR_END]);
	if (g_glob.perv_fd)
		close(g_glob.perv_fd);
	g_glob.perv_fd = p_fd[RD_END];
	if (node_cmd->in > 0)
		close(node_cmd->in);
	if (node_cmd->out > 1)
		close(node_cmd->out);
	if (node_cmd->in != STDIN_FILENO)
		close(p_fd[RD_END]);
	return (pid);
}

void	ft_run_cmds(t_cmds *shel_l)
{
	t_cmds	*node_cmd;

	node_cmd = shel_l;
	if (node_cmd && node_cmd->next == NULL && ft_isbuiltin(node_cmd))
		return (exe_builtin(node_cmd));
	else
	{
		while (node_cmd)
		{
			if (check_exe(node_cmd))
			{
				ft_arrfreey();
				g_glob.last_pid = ft_cmd_exe(shel_l, node_cmd);
			}
			else if (!check_exe(node_cmd))
			{
				ft_arrfreey();
				return ;
			}
			node_cmd = node_cmd->next;
		}
		g_glob.perv_fd = 0;
		ft_wait_cmd();
	}
}
