/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:51:19 by midfath           #+#    #+#             */
/*   Updated: 2022/10/04 19:55:58 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <exe.h>

int sub_process(t_cmds *node_cmd)
{
	if (execve(node_cmd->path, node_cmd->args, glob.env))
		return (-1);
}

int	ft_cmd_exe(t_cmds *node_cmd)
{
	pid_t	pid;
	
	if (fork() == -1)
		return (-1);
	else if (!pid)
		return (sub_process(node_cmd));
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
	while (wait(NULL) != -1)
		;
	return (NULL);
}
