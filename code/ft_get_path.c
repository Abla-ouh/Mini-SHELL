/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:31:21 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/27 21:47:00 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// void	help_get_path(t_cmds *cmds, char *tmp, int i, char *path)
// {
// 	char	*cmd_path;

// 	tmp = ft_substr(path, 0, i);
// 	cmd_path = ft_strjoin(tmp, "/");
// 	free(tmp);
// 	tmp = ft_strjoin(cmd_path, cmds->args[0]);
// 	free(cmd_path);
// }
char	*ft_null_path(char *str)
{
	if (str && ft_strchr(str, '/'))
		return (ft_strdup(str));
	else
		return (NULL);
}

char	*get_cmd_path(t_cmds *cmds)
{
	char	*path;
	char	*tmp;
	char	*cmd_path;
	int		i;

	i = -1;
	tmp = NULL;
	path = return_value("PATH");
	if ((cmds->args[0] && ft_strchr(cmds->args[0], '/')) || !path)
		return (ft_null_path(cmds->args[0]));
	while (path[++i])
	{
		if (path[i] == ':')
		{
			cmd_path = ft_strjoin(ft_substr(path, 0, i), "/");
			tmp = ft_strjoin(cmd_path, cmds->args[0]);
			free(cmd_path);
			if (access(tmp, X_OK) == 0)
				return (tmp);
			free(tmp);
			path += i + 1;
			i = -1;
		}
	}
	return (NULL);
}
