/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:51:19 by midfath           #+#    #+#             */
/*   Updated: 2022/10/12 18:38:24 by midfath          ###   ########.fr       */
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
	
	pid = fork();
	if (pid == -1)
		return (-1);
	else if (!pid)
		return (sub_process(node_cmd));
	ft_wait_cmd(pid);	
	return (0);
}

void	ft_exec(t_cmds *shel_l)
{
	t_cmds *node_cmd;
	int		flag;
	
	flag = 0;
	node_cmd = shel_l;
	if (node_cmd->next == NULL)
		flag = ft_isbuiltin(shel_l);
	if (flag != 0)
		run_builtin(shel_l, flag);
	while (node_cmd)
	{
		glob.exit_status = ft_cmd_exe(node_cmd);
		node_cmd = node_cmd->next;
	}
	return ;
}

int	ft_isbuiltin(t_cmds *shel_l)
{
	if (!ft_strcmp(shel_l->args[0] ,"cd"))
		return (1);
	else if ((!ft_strcmp(shel_l->args[0] ,"exit")))
		return (2);
	else if ((!ft_strcmp(shel_l->args[0] ,"export")))
		return (3);
	else if ((!ft_strcmp(shel_l->args[0] ,"echo")))
		return (4);
	else if ((!ft_strcmp(shel_l->args[0] ,"unset")))
		return (5);
	else if ((!ft_strcmp(shel_l->args[0] ,"env")))
		return (6);
	else if ((!ft_strcmp(shel_l->args[0] ,"pwd")))
		return (7);
	return (0);
}

int	run_builtin(t_cmds *shel_l, int flag)
{
	if (flag == 1)
		return (ft_cd(shel_l->args));
	else if (flag == 2)
		return (ft_exit(shel_l->args));
	else if (flag == 3)
		return (ft_export(shel_l->args));
	else if (flag == 4)
		return (ft_echo(shel_l->args));
	else if (flag == 5)
		return (0);
	//TODO: UNSET
	else if (flag == 6)
		return (ft_env(shel_l->args ,glob.envx));
	else if (flag == 7)
		return (ft_pwd(shel_l->args));
	return (0);
}