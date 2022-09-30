/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:53:46 by midfath           #+#    #+#             */
/*   Updated: 2022/09/30 15:59:46 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exe.h>

int	ft_cd(t_list env,char **argv , )

/*
◦ cd with only a relative or absolute path

** note : Here the directory change is performed
**		chdir is performed
**		OLDPWD is updated if needed,
**		gdata->cwd is always updated as it tracks the real cwd
**		Finally, the PWD is updated if needed
**
** RETURN:	1 on success
**			0 if an error occured (malloc)
**			-1 if an error occured (chdir)
*/

int	ft_getp_cwd(char **p_cwd)
{
	if (!(getcwd(*p_cwd, ft_strlen(*p_cwd))))
		{
			errno = 0;
			ft_leak((void **)p_cwd);
			*p_cwd = getcwd(NULL, 0);
			if (!(*p_cwd))
				return (0);
		}
	return (1);
}


int	chdir_update(char *dir, t_list *env,t_gexe *gdexe)
{
	char	**o_pwd;
	char	**pwd_env;

	pwd_env = find_title(env, "PWD");
	o_pwd = find_title(env, "OLDPWD");
	if (chdir(dir) == -1)
		return (-1);
	if (o_pwd)
	{
		free(*o_pwd);
		*o_pwd = ft_strdup(gdexe->p_cwd);
		if (!(*o_pwd))
			return (0);
	}
	if (!(ft_getp_cwd(&gdexe->p_cwd)) && pwd_env && ft_getp_cwd(pwd_env) == 0)
			return (0);
	return (1);
}