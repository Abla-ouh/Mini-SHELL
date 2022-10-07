/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:29:26 by midfath           #+#    #+#             */
/*   Updated: 2022/10/07 18:21:08 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exe.h>

void	ft_wait_cmd(pid_t pid)
{
	waitpid(pid, &glob.exit_status, 0);
	if (glob.exit_status != 2 && glob.exit_status != 3)
		glob.exit_status = WEXITSTATUS(glob.exit_status);
	else
		glob.exit_status += 128;
	while (wait(NULL) != -1)
	{
	}	
}