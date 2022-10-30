/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:31:21 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/30 14:06:10 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_null_path(char *str)
{
	if (str && ft_strchr(str, '/'))
		return (ft_strdup(str));
	else
		return (NULL);
}

static char	*find_path(char *path, char *tmp, int *i, t_cmds	*cmds)
{
	char	*cmd_path;
	char	*buff;

	buff = ft_substr(path, 0, *i);
	cmd_path = ft_strjoin(buff, "/");
	tmp = ft_strjoin(cmd_path, cmds->args[0]);
	free(cmd_path);
	free(buff);
	if (access(tmp, X_OK) == 0)
		return (tmp);
	free(tmp);
	return (NULL);
}

char	*get_cmd_path2(char *path, char*tmp_path, t_cmds *cmds)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = 0;
	while (path[++i])
	{
		if (path[i] == ':')
		{
			tmp = find_path(path, tmp, &i, cmds);
			if (tmp)
			{
				free(tmp_path);
				return (tmp);
			}
			path += i + 1;
			i = -1;
		}
	}
	if (tmp)
		free(tmp);
	free(tmp_path);
	return (NULL);
}

char	*get_cmd_path(t_cmds *cmds)
{
	char	*path;
	char	*tmp_path;

	tmp_path = return_value("PATH");
	path = tmp_path;
	if ((cmds->args[0] && ft_strchr(cmds->args[0], '/')) || !path)
	{
		(free(path), free(tmp_path));
		return (ft_null_path(cmds->args[0]));
	}
	return (get_cmd_path2(path, tmp_path, cmds));
}
