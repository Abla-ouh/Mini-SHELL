/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:51:19 by midfath           #+#    #+#             */
/*   Updated: 2022/10/07 09:30:05 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <exe.h>

int sub_process(t_cmds *node_cmd)
{
	if (execve(node_cmd->path, node_cmd->args, glob.env))
		return (-1);
	return (0);
}

int	ft_cmd_exe(t_cmds *node_cmd)
{
	pid_t	pid;
	
	pid = 0;
	if (fork() == -1)
		return (-1);
	else if (!pid)
		return (sub_process(node_cmd));
	ft_wait_cmd(pid);	
	return (0);
}

void	ft_exec(t_cmds *lst_cmds)
{
	t_cmds *node_cmd;

	node_cmd = lst_cmds;
	while (node_cmd)
	{
		glob.exit_status = ft_cmd_exe(node_cmd);
		node_cmd = node_cmd->next;
	}
	return ;
}
