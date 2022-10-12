/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:53:46 by midfath           #+#    #+#             */
/*   Updated: 2022/10/12 18:01:40 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exe.h>

int	ft_cd(char **av)
{
	int	r;

	if (!av[1])
	 	r = cd_option("HOME");
	else if (!ft_strcmp("-", av[1]))
		r = cd_option("OLDPWD");
	else
		r = chdir_update(av[1]);
	if (errno)
		perror(strerror(errno));
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

int	cd_option(char *path)
{
	char	*dir;

	dir = getenv(path);
	if (!dir)
	{
		ft_putstr_fd("minishell: cd: `", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("': environment variable not set\n", 2);
		return (-1);
	}
	return (chdir_update(dir));
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

int	chdir_update(char *dir)
{
	char	**o_pwd;
	char	**cwd;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	o_pwd = find_title("OLDPWD");
	cwd = find_title("PWD");
	if (chdir(dir) == -1)
		return (-1);
	if (o_pwd)
	{
		free(*o_pwd);
		*o_pwd = ft_strdup(pwd);
		if (!(*o_pwd))
			return (0);
	}
	if (!(pwd))
		return (0);
	return (1);
}
