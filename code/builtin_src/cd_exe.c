/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:53:46 by midfath           #+#    #+#             */
/*   Updated: 2022/10/20 17:59:58 by midfath          ###   ########.fr       */
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
	return (r);
}

int	cd_option(char *path)
{
	char	**dir;

	dir = find_title(path);
	if (!(dir))
	{
		ft_perror("cd", path, "environment variable not set");
		return (-1);
	}
	return (chdir_update(*dir));
}

int	chdir_update(char *dir)
{
	char	**o_pwd;
	char	*cwd;
	
	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = *find_title("PWD");
	o_pwd = find_title("OLDPWD");
	if (chdir(dir) == -1)
	{
		free(cwd);
		return (-1);
	}
	if (o_pwd)
	{
		free(*o_pwd);
		*o_pwd = ft_strdup(cwd);
		if (!(*o_pwd))
			return (0);
	}
	else if (!o_pwd)
	{
		o_pwd = (char **)malloc(sizeof(char) * 2);
		o_pwd[0] = "OLDPWD";
		o_pwd[1] = ft_strdup(cwd);
		var_update(o_pwd);
	}
	pwd_update();
	return (1);
}

void	pwd_update(void)
{
	char **new_pwd;
	char *pwd;
	
	new_pwd = find_title("PWD");
	if (new_pwd)
	{
		free(*new_pwd);
		*new_pwd = NULL;
		pwd = getcwd(NULL, 0);
		if (pwd)
			*new_pwd = ft_strdup(pwd);
	}
	else
		return ;
}