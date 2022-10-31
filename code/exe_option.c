/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_option.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:22:17 by midfath           #+#    #+#             */
/*   Updated: 2022/10/31 16:09:37 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exe.h>

void	redi_sub(t_cmds *node_cmd, int *p_fd)
{
	if (node_cmd->in != STDIN_FILENO)
	{
		dup2(node_cmd->in, STDIN_FILENO);
		if (g_glob.perv_fd != 0)
			close(g_glob.perv_fd);
	}
	else if (g_glob.perv_fd != 0)
		dup2(g_glob.perv_fd, STDIN_FILENO);
	if (node_cmd->out != STDOUT_FILENO)
	{
		dup2(node_cmd->out, STDOUT_FILENO);
	}
	else if (node_cmd->next)
		dup2(p_fd[WR_END], STDOUT_FILENO);
	close(p_fd[WR_END]);
}

void	exe_file(t_cmds *node_cmd)
{
	DIR	*dir;

	if (execve(node_cmd->path, node_cmd->args, g_glob.env) == -1)
	{
		dir = opendir(node_cmd->args[0]);
		if (dir)
		{
			ft_arrfreey();
			ft_perror(NULL, node_cmd->args[0], "is a directory");
			closedir(dir);
			exit (126);
		}
		else
		{
			ft_arrfreey();
			ft_perror(NULL, node_cmd->args[0], "No such file or directory");
			exit (127);
		}
	}
}

void	exe_builtin(t_cmds *node_cmd)
{
	int	flag;

	flag = ft_isbuiltin(node_cmd);
	if (flag != 0 && (node_cmd->in != STDIN_FILENO || \
	node_cmd->out != STDOUT_FILENO))
	{
		if (node_cmd->in != STDIN_FILENO)
		{
			dup2(node_cmd->in, STDIN_FILENO);
			close(node_cmd->in);
		}
		if (node_cmd->out != STDOUT_FILENO)
		{
			dup2(node_cmd->out, STDOUT_FILENO);
			close(node_cmd->out);
		}
	}
	if (flag != 0)
	{
		g_glob.exit_status = run_builtin(node_cmd, flag);
		dup2(g_glob.infd, STDIN_FILENO);
		dup2(g_glob.outfd, STDOUT_FILENO);
	}
}

int	exe_cmd(t_cmds *node_cmd)
{
	char	**p;

	p = find_title("PATH");
	if (p && (execve(node_cmd->path, node_cmd->args, g_glob.env) == -1))
	{	
		ft_arrfreey();
		ft_perror(NULL, node_cmd->args[0], "command not found");
		exit(127);
	}
	else if (!p)
	{
		ft_arrfreey();
		ft_perror(NULL, node_cmd->args[0], "No such file or directory");
		exit(127);
	}
	exit (127);
}
