/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:05:12 by midfath           #+#    #+#             */
/*   Updated: 2022/10/31 19:35:21 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exe.h>

int	var_cat(char **var)
{
	char	**r_write;
	int		len;
	char	*tmp;

	r_write = find_title(var[0]);
	if (r_write)
	{
		len = ft_strlen(*r_write) + ft_strlen(var[1]);
		tmp = ft_strdup(*r_write);
		free(*r_write);
		*r_write = ft_strjoin(tmp, var[1]);
		free(tmp);
		if (!(*r_write))
			return (1);
		free_2d_char(var);
	}
	else
		return (var_update(var));
	return (0);
}

void	var_export(char **var, t_list *new)
{
	t_env	*ret;

	ret = init_lst_env();
	if (!ret)
		return ;
	ret->title = ft_strdup(var[0]);
	ret->value = ft_strdup(var[1]);
	if (!var[1])
	{
		free(ret->value);
		ret->value = NULL;
	}
	new = ft_lstnew((t_env *)ret);
	if (!new)
		ft_leak((void *)new);
	ft_lstadd_back(&g_glob.envx, new);
	new->next = NULL;
	free_2d_char(var);
}

int	var_update(char **var)
{
	t_list	*new;
	char	**r_write;

	new = NULL;
	r_write = find_title(var[0]);
	if (r_write)
	{
		if (var[1])
		{	
			*r_write = ft_strdup(var[1]);
			free_2d_char(var);
			return (0);
		}
		if (!(r_write))
		{
			free_2d_char(var);
			return (1);
		}
	}
	else
		var_export(var, new);
	return (0);
}

char	**get_var(char *str)
{
	int		i;
	char	**new_var;

	i = 0;
	new_var = (char **)malloc(sizeof(char *) * 3);
	new_var[0] = NULL;
	new_var[1] = NULL;
	new_var[2] = NULL;
	while (str[i] && str[i] != '=')
		i++;
	new_var[0] = ft_substr(str, 0, i);
	if (!str[i])
	{
		free(new_var[1]);
		new_var[1] = NULL;
	}
	else
		new_var[1] = ft_strdup(str + i + 1);
	return (new_var);
}

char	**find_title(char *title)
{
	t_list	*tmp;

	tmp = g_glob.envx;
	while (tmp)
	{
		if (((t_env *)tmp->content)->title)
		{
			if (!ft_strcmp(((t_env *)tmp->content)->title, title))
				return (&((t_env *)tmp->content)->value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
