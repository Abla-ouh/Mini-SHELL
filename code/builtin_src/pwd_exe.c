/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:03:28 by midfath           #+#    #+#             */
/*   Updated: 2022/10/12 18:44:51 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exe.h>

int	ft_pwd(char **ar)
{
	char *cwd;
	if (ar[1])
		return(errno);
	glob.exit_status = 0;
	cwd =  getcwd(NULL, 0);
	ft_putstr(cwd);
	return (1);
}