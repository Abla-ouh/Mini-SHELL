/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:03:28 by midfath           #+#    #+#             */
/*   Updated: 2022/10/13 18:52:00 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exe.h>

int	ft_pwd(char **ar)
{
	char *cwd;
	
	(void)ar;
	glob.exit_status = 0;
	cwd =  getcwd(NULL, 0);
	ft_putendl_fd(cwd, 1);
	return (1);
}
