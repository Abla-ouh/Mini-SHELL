/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:53:46 by midfath           #+#    #+#             */
/*   Updated: 2022/10/13 19:05:18 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exe.h>

int	ft_cd(char **av)
{
	int	r;

	r = 0;
	if (!av[1])
	 	r = cd_option("HOME");
	else if (!ft_strcmp("-", av[1]))
		r = cd_option("OLDPWD");
	else
		r = chdir_update(av[1]);
	if (r == -1)
	{
		ft_putstr_fd("minishell: cd: `", 2);
		ft_putendl_fd(strerror(errno), 2);
	}	
	return (r);
}

int	cd_option(char *path)
{
	char	**dir;

	dir = find_title(path);
	if (!(dir))
	{
		ft_putstr_fd("minishell: cd: `", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("': environment variable not set\n", 2);
		return (-1);
	}
	return (chdir_update(*dir));
}

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
	return (1);
}
