/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:51:19 by midfath           #+#    #+#             */
/*   Updated: 2022/10/22 10:59:20 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <exe.h>

void	close_all_fds(t_cmds *shel_l)
{
	t_cmds *nodes;
	
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

int sub_process(t_cmds *shel_l, t_cmds *node_cmd, int *p_fd)
{
	int 	f;
	
	f = 0;
	redi_sub(node_cmd ,p_fd);
	close(p_fd[RD_END]);
	close_all_fds(shel_l);
	f = ft_isbuiltin(node_cmd);
	if (f) 
		run_builtin(node_cmd, f);
	else
	{
		if (execve(node_cmd->path, node_cmd->args, glob.env) == -1)
			ft_perror(NULL, NULL, NULL);
	}
	exit(1);
}

int	ft_cmd_exe(t_cmds *shel_l, t_cmds *node_cmd)
{
	pid_t	pid;
	int	p_fd[2];
	
	if (pipe(p_fd) == -1) 
		exit (1);
	glob.env = env_lst_to_matrix(glob.envx);
	pid = fork();
	if (pid == -1)
		exit (1);
	if (!pid)
		return (sub_process(shel_l, node_cmd, p_fd));
	close(p_fd[WR_END]);
	if (glob.perv_fd)
		close(glob.perv_fd);
	glob.perv_fd = p_fd[RD_END];
	return (pid);
}

void	ft_run_cmds(t_cmds *shel_l)
{
	t_cmds	*node_cmd;
	pid_t	pid;
	int		flag;

	flag = 0;
	node_cmd = shel_l;
	if (node_cmd && node_cmd->next == NULL && check_execut(node_cmd))
		flag = ft_isbuiltin(shel_l);
	if (flag != 0)
		glob.exit_status = run_builtin(shel_l, flag);
	else
	{
		while (node_cmd)
		{
			if (check_execut(node_cmd))
				pid = ft_cmd_exe(shel_l, node_cmd);
			else if (shel_l->args[0])
			{
				ft_perror("minishell", NULL, NULL);
				return ;
			}
			node_cmd = node_cmd->next;
		}
		glob.perv_fd = 0;
		ft_wait_cmd(pid);
	}
	return ;
}
