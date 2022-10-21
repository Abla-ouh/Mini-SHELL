/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_option.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:22:17 by midfath           #+#    #+#             */
/*   Updated: 2022/10/18 16:33:51 by midfath          ###   ########.fr       */
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
