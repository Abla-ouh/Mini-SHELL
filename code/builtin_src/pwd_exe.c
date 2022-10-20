/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:03:28 by midfath           #+#    #+#             */
/*   Updated: 2022/10/14 17:24:15 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exe.h>

int	ft_pwd(char **ar)
{
	char *cwd;
	
	(void)ar;
	glob.exit_status = 0;
	cwd =  getcwd(NULL, 0);
	if (!cwd)
		cwd = *find_title("PWD");
	ft_putendl_fd(cwd, 1);
	return (1);
}

