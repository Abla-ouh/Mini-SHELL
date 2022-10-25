/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:31:21 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/25 01:25:24 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_cmd_path(t_cmds *cmds)
{
	char	*path;
	char	*cmd_path;
	char	*tmp;
	int		i;

	i = 0;
	if (cmds->args[0] && ft_strchr(cmds->args[0], '/'))
		return (ft_strdup(cmds->args[0]));
	path = return_value("PATH");
	if (!path)
		return (NULL);
	while (path[i])
	{
		if (path[i] == ':')
		{
			tmp = ft_substr(path, 0, i);
			cmd_path = ft_strjoin(tmp, "/");
			free(tmp);
			tmp = ft_strjoin(cmd_path, cmds->args[0]);
			free(cmd_path);
			if (access(tmp, X_OK) == 0)
				return (tmp);
			free(tmp);
			path += i + 1;
			i = 0;
		}
		i++;
	}
	return (NULL);
}