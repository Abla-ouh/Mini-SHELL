/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:53:46 by midfath           #+#    #+#             */
/*   Updated: 2022/11/01 16:36:09 by midfath          ###   ########.fr       */
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
		ft_perror("cd", NULL, NULL);
	else if (r == -2)
		ft_perror(NULL, "cd", "error retrieving current directory: getcwd: \
	 cannot access parent directories: No such file or directory");
	if ((r == -2) || (r == -1))
		return (1);
	else
		return (0);
}

int	cd_option(char *path)
{
	char	**dir;

	dir = find_title(path);
	if (!(dir))
	{
		ft_perror("cd", path, "environment variable not set");
		return (1);
	}
	return (chdir_update(*dir));
}

int	chdir_update(char *dir)
{
	char	**o_pwd;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	o_pwd = find_title("OLDPWD");
	if (chdir(dir) == -1 || (!(cwd) && !ft_strcmp(dir, ".")))
	{
		if (!cwd)
			return (-2);
		else
		{
			free(cwd);
			return (-1);
		}
	}
	return (path_changer(o_pwd, cwd));
}

int	path_changer(char **o_pwd, char *cwd)
{
	if (!cwd)
		cwd = return_value("PWD");
	if (o_pwd)
	{
		free(*o_pwd);
		*o_pwd = NULL;
		*o_pwd = ft_strdup(cwd);
		free(cwd);
	}
	else
	{
		o_pwd = malloc(sizeof(char *) * 3);
		o_pwd[0] = ft_strdup("OLDPWD");
		o_pwd[1] = ft_strdup(cwd);
		o_pwd[2] = NULL;
		var_update(o_pwd);
	}
	pwd_update();
	return (0);
}

void	pwd_update(void)
{
	char	**new_pwd;
	char	*pwd;

	new_pwd = find_title("PWD");
	if (new_pwd)
	{
		pwd = getcwd(NULL, 0);
		if (pwd)
		{
			free(*new_pwd);
			*new_pwd = NULL;
			*new_pwd = getcwd(NULL, 0);
			free(pwd);
		}
	}
	else
		return ;
}
