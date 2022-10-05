/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:53:46 by midfath           #+#    #+#             */
/*   Updated: 2022/10/05 14:04:20 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exe.h>

int	ft_cd(t_list *env ,char **av ,t_gexe *gdexe)
{
	int	r;

	if (!ft_strcmp(av[1], "~") || !av[1])
		r = cd_option("HOME", env, gdexe);
	else if (!ft_strcmp("-", av[1]))
	{
		r = cd_option("OLDPWD", env, gdexe);
	}
	else
		r = chdir_update(av[1], env, gdexe);
	if (errno)
		printf("%s: %s",av[0] ,strerror(errno));
	return (r);
}

/*
◦ cd with only a relative or absolute path

** note : Here the directory change is performed
**		chdir is performed
**		OLDPWD is updated if needed,
**		gdexe->pcwd is always updated as it tracks the real cwd
**		Finally, the PWD is updated if needed
**
** RETURN:	1 on success
**			0 if an error occured (malloc)
**			-1 if an error occured (chdir)
*/

int	cd_option(char *path, t_list *env, t_gexe *gdexe)
{
	char	*dir;

	dir = getenv(path);
	if (!dir)
		return (-1);
	return (chdir_update(dir, env, gdexe));
}

// int	ft_getp_cwd(char **p_cwd)
// {
// 	if (!(getcwd(*p_cwd, ft_strlen(*p_cwd))))
// 		{
// 			errno = 0;
// 			ft_leak((void **)p_cwd);
// 			*p_cwd = getcwd(NULL, 0);
// 			if (!(*p_cwd))
// 				return (0);
// 		}
// 	return (1);
// }


// int	chdir_update(char *dir, t_list *env ,t_gexe *gdexe)
// {
// 	char	**o_pwd;
// 	char	**pwd_env;

// 	pwd_env = find_title(env, "PWD");
// 	o_pwd = find_title(env, "OLDPWD");
// 	if (chdir(dir) == -1)
// 		return (-1);
// 	if (o_pwd)
// 	{
// 		free(*o_pwd);
// 		*o_pwd = ft_strdup(gdexe->p_cwd);
// 		if (!(*o_pwd))
// 			return (0);
// 	}
// 	if (!(ft_getp_cwd(&gdexe->p_cwd)) && pwd_env && ft_getp_cwd(pwd_env) == 0)
// 			return (0);
// 	return (1);
// }

