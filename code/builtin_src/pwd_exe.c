/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:03:28 by midfath           #+#    #+#             */
/*   Updated: 2022/10/22 15:41:28 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exe.h>

int	ft_pwd(char **ar)
{
	char *cwd;
	
	(void)ar;
	cwd =  getcwd(NULL, 0);
	if (!cwd)
	{
		cwd = return_value("PWD");
		ft_putstr(cwd);
		ft_putstr("\n");
		return (0);
	}
	ft_putendl_fd(cwd, 1);
	free(cwd);
	return (0);
}
