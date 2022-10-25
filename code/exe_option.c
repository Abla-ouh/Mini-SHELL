/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_option.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:22:17 by midfath           #+#    #+#             */
/*   Updated: 2022/10/25 01:00:21 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exe.h>

void	redi_sub(t_cmds *node_cmd ,int *p_fd)
{
	if (node_cmd->in != STDIN_FILENO)
	{
		dup2(node_cmd->in , STDIN_FILENO);
		if (glob.perv_fd != 0)
			close(glob.perv_fd);
	}
	else if (glob.perv_fd != 0)
		dup2(glob.perv_fd, STDIN_FILENO);
	if (node_cmd->out != STDOUT_FILENO)
	{
		dup2(node_cmd->out, STDOUT_FILENO);
		close(node_cmd->out);
	}
	else if (node_cmd->next)
		dup2(p_fd[WR_END], STDOUT_FILENO);
	close(p_fd[WR_END]);
	return ;
}

void	exe_file(t_cmds *node_cmd)
{
	DIR	*dir;

	execve(node_cmd->path, node_cmd->args, glob.env);
	dir = opendir(node_cmd->args[0]);
	if (dir)
	{
		ft_perror("minishell", node_cmd->args[0], "No such file or directory");
		closedir(dir);
	}
	else
		ft_perror("minishell", node_cmd->args[0], "command not found");
	
}


void	exe_cmd(t_cmds *node_cmd)
{
	char	**p;

	p = find_title("PATH");
	if (!p)
	{
		if (execve(node_cmd->path, node_cmd->args, glob.env) == -1)
			ft_perror("minishell", node_cmd->args[0], "No such file or directory");
	}
	else if (ft_strchr(node_cmd->path, '/'))
	{
		if (execve(node_cmd->path, node_cmd->args, glob.env) == -1)
			ft_perror("minishell", node_cmd->args[0], "command not found");
	}
	else
		ft_perror("minishell", node_cmd->args[0], "command not found");
}